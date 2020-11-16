
#include "easypap.h"
#include "rle_lexer.h"

#include <omp.h>
#include <stdbool.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

static unsigned color = 0xFFFF00FF; // Living cells have the yellow color

typedef char cell_t;
static cell_t *change_table;
// typedef unsigned cell_t;

static cell_t *restrict _table = NULL, *restrict _alternate_table = NULL;

static inline cell_t *table_cell(cell_t *restrict i, int y, int x) {
  return i + y * DIM + x;
}

// This kernel does not directly work on cur_img/next_img.
// Instead, we use 2D arrays of boolean values, not colors
#define cur_table(y, x) (*table_cell(_table, (y), (x)))
#define next_table(y, x) (*table_cell(_alternate_table, (y), (x)))

void life_init(void) {

  // life_init may be (indirectly) called several times so we check if data were
  // already allocated
  if (_table == NULL) {
    const unsigned size = DIM * DIM * sizeof(cell_t);

    change_table =
        mmap(NULL, (DIM * DIM) / 32 + 1 * sizeof(cell_t),
             PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    PRINT_DEBUG('u', "Memory footprint = 2 x %d bytes\n", size);

    _table = mmap(NULL, size, PROT_READ | PROT_WRITE,
                  MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    _alternate_table = mmap(NULL, size, PROT_READ | PROT_WRITE,
                            MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  }
}

void life_finalize(void) {
  const unsigned size = DIM * DIM * sizeof(cell_t);

  munmap(_table, size);
  munmap(_alternate_table, size);
  munmap(change_table, (DIM * DIM) / 32 + 1 * sizeof(cell_t));
}

// This function is called whenever the graphical window needs to be refreshed
void life_refresh_img(void) {
  for (int i = 0; i < DIM; i++)
    for (int j = 0; j < DIM; j++)
      cur_img(i, j) = cur_table(i, j) * color;
}

static inline void swap_tables(void) {
  cell_t *tmp = _table;

  _table = _alternate_table;
  _alternate_table = tmp;
}

///////////////////////////// Sequential version (seq)

static int compute_new_state(int y, int x) {
  unsigned n = 0;
  unsigned me = cur_table(y, x) != 0;
  unsigned change = 0;

  if (x > 0 && x < DIM - 1 && y > 0 && y < DIM - 1) {

    for (int i = y - 1; i <= y + 1; i++)
      for (int j = x - 1; j <= x + 1; j++)
        n += cur_table(i, j);

    n = (n == 3 + me) | (n == 3);
    if (n != me)
      change |= 1;

    next_table(y, x) = n;
  }

  return change;
}

unsigned life_compute_seq(unsigned nb_iter) {
  for (unsigned it = 1; it <= nb_iter; it++) {
    int change = 0;

    monitoring_start_tile(0);

    for (int i = 0; i < DIM; i++)
      for (int j = 0; j < DIM; j++)
        change |= compute_new_state(i, j);

    monitoring_end_tile(0, 0, DIM, DIM, 0);

    swap_tables();

    if (!change)
      return it;
  }

  return 0;
}

///////////////////////////// Tiled sequential version (tiled)

// Tile inner computation
static int do_tile_reg(int x, int y, int width, int height) {
  int change = 0;

  for (int i = y; i < y + height; i++)
    for (int j = x; j < x + width; j++)
      change |= compute_new_state(i, j);

  return change;
}

static int do_tile(int x, int y, int width, int height, int who) {
  int r;

  monitoring_start_tile(who);

  r = do_tile_reg(x, y, width, height);

  monitoring_end_tile(x, y, width, height, who);

  return r;
}

unsigned life_compute_tiled(unsigned nb_iter) {
  unsigned res = 0;

  for (unsigned it = 1; it <= nb_iter; it++) {
    unsigned change = 0;

    for (int y = 0; y < DIM; y += TILE_SIZE)
      for (int x = 0; x < DIM; x += TILE_SIZE)
        change |= do_tile(x, y, TILE_SIZE, TILE_SIZE, 0);

    swap_tables();

    if (!change) { // we stop when all cells are stable
      res = it;
      break;
    }
  }

  return res;
}

///////////////////////////// omp for version
static int compute_new_state_ompfor(int y, int x) {
  unsigned n = 0;
  unsigned me = cur_table(y, x) != 0;
  unsigned change = 0;

  for (int i = y - 1; i <= y + 1; i++)
    for (int j = x - 1; j <= x + 1; j++)
      n += cur_table(i, j);

  n = (n == 3 + me) | (n == 3);
  if (n != me)
    change |= 1;

  next_table(y, x) = n;

  return change;
}

static int do_tile_reg_ompfor(int x, int y, int width, int height) {
  int change = 0;
  for (int i = y; i < y + height; i++)
    for (int j = x; j < x + width; j++) {
      if (j > 0 && j < DIM - 1 && i > 0 && i < DIM - 1) {
        change |= compute_new_state_ompfor(i, j);
      }
    }

  return change;
}

static int do_tile_ompfor(int x, int y, int width, int height, int who) {
  int r;

  monitoring_start_tile(who);

  r = do_tile_reg_ompfor(x, y, width, height);

  monitoring_end_tile(x, y, width, height, who);

  return r;
}

unsigned life_compute_ompfor(unsigned nb_iter) {
  unsigned res = 0;
  unsigned change = 0;
  unsigned changetmp = 0;
#pragma omp parallel firstprivate(changetmp)
  for (unsigned it = 1; it <= nb_iter; it++) {
#pragma omp single
    change = 0;
    changetmp = 0;
#pragma omp for collapse(2) reduction(| : change) schedule(static)
    for (int y = 0; y < DIM; y += TILE_SIZE) {
      for (int x = 0; x < DIM; x += TILE_SIZE) {
        changetmp |=
            do_tile_ompfor(x, y, TILE_SIZE, TILE_SIZE, omp_get_thread_num());
        change = change | changetmp;
      }
    }
#pragma omp single
    swap_tables();
    if (!change) { // we stop when all cells are stable
      res = it;
      break;
    }
  }

  return res;
}

///////////////////////////// optimisation mémoire

#include <immintrin.h>

static int do_tile_reg_256(int x, int y) {
  int change = 0;

  __m256i haut, milieu, bas, somme, next_i, n, gauche, droit;

  haut = _mm256_loadu_si256((const __m256i *)&cur_table(y - 1, x));
  milieu = _mm256_loadu_si256((const __m256i *)&cur_table(y, x));
  bas = _mm256_loadu_si256((const __m256i *)&cur_table(y + 1, x));

  somme = _mm256_add_epi8(haut, _mm256_add_epi8(milieu, bas));

  int milieu_droit = _mm256_extract_epi8(somme, 16);
  int milieu_gauche = _mm256_extract_epi8(somme, 15);
  int completion_gauche = 0;
  int completion_droite = 0;

  if (x > 0) {
    completion_gauche =
        cur_table(y - 1, x - 1) + cur_table(y, x - 1) + cur_table(y + 1, x - 1);
  }
  if (x + 32 < DIM) {
    completion_droite = cur_table(y - 1, x + 32) + cur_table(y, x + 32) +
                        cur_table(y + 1, x + 32);
  }

  __m256i completion =
      _mm256_set_epi8(completion_droite, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, milieu_gauche, milieu_droit, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, completion_gauche);

  gauche = _mm256_slli_si256(somme, 1);
  droit = _mm256_srli_si256(somme, 1);

  n = _mm256_add_epi8(
      somme, _mm256_add_epi8(completion, _mm256_add_epi8(gauche, droit)));

  next_i = _mm256_or_si256(
      _mm256_cmpeq_epi8(n, _mm256_set1_epi8(3)),
      _mm256_cmpeq_epi8(n, _mm256_add_epi8(_mm256_set1_epi8(3), milieu)));

  next_i =
      _mm256_and_si256(next_i, _mm256_set1_epi8(1)); // set à 1 au lieu de 255

  change |= !_mm256_testz_si256(_mm256_set1_epi8(255),
                                _mm256_xor_si256(next_i, milieu));

  _mm256_store_si256((__m256i *)&next_table(y, x), next_i);
  return change;
}

static int do_tile_256(int x, int y, int width, int height, int who) {
  int r = 0;
  monitoring_start_tile(who);

  r = do_tile_reg_256(x, y);

  monitoring_end_tile(x, y, width, height, who);
  return r;
}

unsigned life_compute_vec(unsigned nb_iter) {
  unsigned res = 0;
  unsigned change = 0;
  unsigned changetmp = 0;
#pragma omp parallel firstprivate(changetmp)
  for (unsigned it = 1; it <= nb_iter; it++) {

#pragma omp for collapse(2) reduction(| : change) schedule(static)
    for (int y = 1; y < DIM - 1; y += 1) {
      for (int x = 0; x < DIM - 1; x += 32) {
        changetmp |= do_tile_256(x, y, 32, 1, omp_get_thread_num());
        change = change | changetmp;
      }
    }
#pragma omp single
    swap_tables();
    if (!change) { // we stop when all cells are stable
      res = it;
      break;
    }
  }

  return res;
}
//////////////////////////////////////////////// version vectorielle paresseusse
static int index_change(int x, int y) {
  return (x / 32 + (y - 1) * ((DIM / 32) + 1));
}

static int test_paresseux(int x, int y) {
  int n = 0;

  if (x > 0 && x < DIM && y > 0 && y < DIM) {
    for (int i = y - 1; i <= y + 1; i++)
      for (int j = x - 1; j <= x + 1; j++)
        n += change_table[index_change(i, j)];
  }
  return n;
}

static int do_tile_256_paress(int x, int y, int width, int height, int who,
                              int nb_iter) {
  int r = 0;
  if (test_paresseux(x, y) > 0 || nb_iter == 1) {
    monitoring_start_tile(who);

    r = do_tile_reg_256(x, y);

    monitoring_end_tile(x, y, width, height, who);
    change_table[index_change(x, y)] = r;
  } else {
    // TODO zone d'ombre ?
    monitoring_start_tile(6);
    monitoring_end_tile(x, y, width, height, 6);
  }
  return r;
}

unsigned life_compute_vecparess(unsigned nb_iter) {
  unsigned res = 0;
  unsigned change = 0;
  unsigned changetmp = 0;
#pragma omp parallel firstprivate(changetmp)
  for (unsigned it = 1; it <= nb_iter; it++) {

#pragma omp for collapse(2) reduction(| : change) schedule(static)
    for (int y = 1; y < DIM - 1; y += 1) {
      for (int x = 0; x < DIM - 1; x += 32) {
        changetmp |= do_tile_256_paress(x, y, 32, 1, omp_get_thread_num(), it);
        change = change | changetmp;
      }
    }
#pragma omp single
    swap_tables();
    if (!change) { // we stop when all cells are stable
      res = it;
      break;
    }
  }

  return res;
}

///////////////////////////// Initial configs

void life_draw_stable(void);
void life_draw_guns(void);
void life_draw_random(void);
void life_draw_clown(void);
void life_draw_diehard(void);
void life_draw_bugs(void);
void life_draw_otca_off(void);
void life_draw_otca_on(void);
void life_draw_meta3x3(void);

static inline void set_cell(int y, int x) {
  cur_table(y, x) = 1;
  if (opencl_used)
    cur_img(y, x) = 1;
}

static inline int get_cell(int y, int x) { return cur_table(y, x); }

static void inline life_rle_parse(char *filename, int x, int y,
                                  int orientation) {
  rle_lexer_parse(filename, x, y, set_cell, orientation);
}

static void inline life_rle_generate(char *filename, int x, int y, int width,
                                     int height) {
  rle_generate(x, y, width, height, get_cell, filename);
}

void life_draw(char *param) {
  if (access(param, R_OK) != -1) {
    // The parameter is a filename, so we guess it's a RLE-encoded file
    life_rle_parse(param, 1, 1, RLE_ORIENTATION_NORMAL);
  } else
    // Call function ${kernel}_draw_${param}, or default function (second
    // parameter) if symbol not found
    hooks_draw_helper(param, life_draw_guns);
}

static void otca_autoswitch(char *name, int x, int y) {
  life_rle_parse(name, x, y, RLE_ORIENTATION_NORMAL);
  life_rle_parse("data/rle/autoswitch-ctrl.rle", x + 123, y + 1396,
                 RLE_ORIENTATION_NORMAL);
}

static void otca_life(char *name, int x, int y) {
  life_rle_parse(name, x, y, RLE_ORIENTATION_NORMAL);
  life_rle_parse("data/rle/b3-s23-ctrl.rle", x + 123, y + 1396,
                 RLE_ORIENTATION_NORMAL);
}

static void at_the_four_corners(char *filename, int distance) {
  life_rle_parse(filename, distance, distance, RLE_ORIENTATION_NORMAL);
  life_rle_parse(filename, distance, distance, RLE_ORIENTATION_HINVERT);
  life_rle_parse(filename, distance, distance, RLE_ORIENTATION_VINVERT);
  life_rle_parse(filename, distance, distance,
                 RLE_ORIENTATION_HINVERT | RLE_ORIENTATION_VINVERT);
}

// Suggested cmdline: ./run -k life -s 2176 -a otca_off -ts 64 -r 10
void life_draw_otca_off(void) {
  if (DIM < 2176)
    exit_with_error("DIM should be at least %d", 2176);

  otca_autoswitch("data/rle/otca-off.rle", 1, 1);
}

// Suggested cmdline: ./run -k life -s 2176 -a otca_on -ts 64 -r 10
void life_draw_otca_on(void) {
  if (DIM < 2176)
    exit_with_error("DIM should be at least %d", 2176);

  otca_autoswitch("data/rle/otca-on.rle", 1, 1);
}

// Suggested cmdline: ./run -k life -s 6208 -a meta3x3 -ts 64 -r 50
void life_draw_meta3x3(void) {
  if (DIM < 6208)
    exit_with_error("DIM should be at least %d", 6208);

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      otca_life(j == 1 ? "data/rle/otca-on.rle" : "data/rle/otca-off.rle",
                1 + j * (2058 - 10), 1 + i * (2058 - 10));
}

// Suggested cmdline: ./run -k life -a bugs -ts 64
void life_draw_bugs(void) {
  for (int y = 0; y < DIM / 2; y += 32) {
    life_rle_parse("data/rle/tagalong.rle", y + 1, y + 8,
                   RLE_ORIENTATION_NORMAL);
    life_rle_parse("data/rle/tagalong.rle", y + 1, (DIM - 32 - y) + 8,
                   RLE_ORIENTATION_NORMAL);
  }
}

void life_draw_stable(void) {
  for (int i = 1; i < DIM - 2; i += 4)
    for (int j = 1; j < DIM - 2; j += 4) {
      set_cell(i, j);
      set_cell(i, j + 1);
      set_cell(i + 1, j);
      set_cell(i + 1, j + 1);
    }
}

void life_draw_guns(void) { at_the_four_corners("data/rle/gun.rle", 1); }

void life_draw_random(void) {
  for (int i = 1; i < DIM - 1; i++)
    for (int j = 1; j < DIM - 1; j++)
      if (random() & 1)
        set_cell(i, j);
}

// Suggested cmdline: ./run -k life -s 256 -a clown -i 110
void life_draw_clown(void) {
  life_rle_parse("data/rle/clown-seed.rle", DIM / 2, DIM / 2,
                 RLE_ORIENTATION_NORMAL);
}

void life_draw_diehard(void) {
  life_rle_parse("data/rle/diehard.rle", DIM / 2, DIM / 2,
                 RLE_ORIENTATION_NORMAL);
}
