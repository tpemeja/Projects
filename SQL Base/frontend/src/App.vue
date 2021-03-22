<template>
  <div id="app">
    <b-navbar toggleable="md" type="dark" variant="primary" class="mb-4">
      <b-navbar-toggle target="nav_collapse"></b-navbar-toggle>
      <b-navbar-brand to="/">CanarDex</b-navbar-brand>
       <b-collapse is-nav id="nav_collapse">
        <b-navbar-nav>
          <b-nav-item to="/ranking">Classement</b-nav-item>
          <b-nav-item to="/encyclopedia">Encyclopédie</b-nav-item>
          <b-nav-item to="/players">Liste des joueurs</b-nav-item>
          <b-nav-item to="/decks">Liste des decks</b-nav-item>
          <b-nav-item to="/addition">Ajouter</b-nav-item>
        </b-navbar-nav>
        <b-navbar-nav class="ml-auto">
                <b-form v-on:submit.prevent="playerSearch" inline>
                    <b-form-group>
                    <b-form-input type="text" id="playerName" placeholder="Pseudo du joueur..." v-model="playerName"></b-form-input>
                </b-form-group>
                <b-form-group>
                    <b-button class="button button-close" type="submit">Rechercher !</b-button>
            </b-form-group>
            </b-form>
        </b-navbar-nav>
      </b-collapse>
    </b-navbar>
    <router-view></router-view>
  </div>
</template>

<script>
import axios from "axios";
import store from "./store";
import router from "./router";

export default {
    data() {
        return {
            playerName: "",
            flag: true
        };
    },
  methods: {
      playerSearch: function(event) {
          this.$store.dispatch("search",this.playerName);
          this.$router.push("/search");
          this.flag = false;
        }
  },
  watch: {
      playerName: function() {
          if (! this.flag) {
              this.$router.push("/");
              this.flag = true;
          }
      }
  },
  created: function() {
      this.flag = true;
  }
};
</script>

<style scoped>
.button {
  border: none;
  border-radius: 2px;
}

.button-close {
  background-color: green;
}

</style>
