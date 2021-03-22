<template>
    <!-- <div class="mx-auto mt-3" style="width: 800px;">-->

    <div   class="v-align">
    <b-container>
        <b-col cols="13">
        <b-list-group-item variant="danger">
            <b-row>
            <b-col cols="11">
                Rang
            </b-col>
            Victoires
        </b-row>
        </b-list-group-item>
          <b-list-group-item  v-for="joueur in liste" v-bind:key="joueur.id">
              <template v-if="isFirst(joueur.NbVictoires)">
                  <b-row>
                  <!--<b-badge variant="warning">{{joueur.NoJoueur}}</b-badge>-->
                  <b-col cols="1">
                  <img src="../assets/firstplace.png" alt="" width="25px">
              </b-col>
                  <b-col cols="10" >
                  {{joueur.Pseudonyme}}
                  (
                  {{joueur.Nom}}
                  {{joueur.Prenom}}
                  )
              </b-col>
              <b-col cols="1">
                  {{joueur.NbVictoires}}
              </b-col>
              </b-row>
          </template>
          <template v-else>
              <template v-if="isSecond(joueur.NbVictoires)">
                  <b-row>
                      <b-col cols="1">
                  <img src="../assets/secondplace.png" alt="" width="25px">
              </b-col>
                  <b-col cols="10" >
                  {{joueur.Pseudonyme}}
                  (
                  {{joueur.Nom}}
                  {{joueur.Prenom}}
                  )
              </b-col>
              <b-col cols="1">
                  {{joueur.NbVictoires}}
              </b-col>
              </b-row>
          </template>
          <template v-else>
              <template v-if="isThird(joueur.NbVictoires)">
                  <b-row>
                      <b-col cols="1">
                  <img src="../assets/thirdplace.png" alt="" width="25px">
              </b-col>
                  <b-col cols="10" >
                  {{joueur.Pseudonyme}}
                  (
                  {{joueur.Nom}}
                  {{joueur.Prenom}}
                  )
              </b-col>
              <b-col cols="1">
                  {{joueur.NbVictoires}}
              </b-col>
              </b-row>
          </template>
          <template v-else>
              <b-row>
                  <b-col cols="1">
                {{joueur.NoJoueur}}
            </b-col>
                <br />
                <b-col cols="10" >
                {{joueur.Pseudonyme}}
                (
                {{joueur.Nom}}
                {{joueur.Prenom}}
                )
            </b-col>
            <b-col cols="1">
                {{joueur.NbVictoires}}
            </b-col>
            </b-row>
          </template>
          </template>
          </template>
        </b-list-group-item>
      </b-col>
</b-container>
</div>
</template>

<script>
import axios from "axios";

export default {
    data(){
     return{
         liste: [],
         count: 0,
         first: -1, // nb de victoires du premier, second puis troisieme
         second: -1,
         third: -1,
         place: 0,
         atSamePlace: 0 // nombre de joueurs à la même place
    }
},
    methods: {
        loadRank: function(event) {
            axios
                .get("http://localhost:3000/players/by/games/won")
                .then(response => {
                    this.liste = response.data;
                    this.loadOthers();
                })
                .catch(e => {
                    console.error(e);
                });
        },
        loadOthers: function(event) {
            axios
                .get("http://localhost:3000/players/by/games/neverWon")
                .then(response => {
                    // ajout des joueurs sans victoire
                    for(var i = 0; i < response.data.length; i++) {
                        this.liste.push(response.data[i]);
                    }
                    this.setRankValue();
                })
                .catch(e => {
                    console.error(e);
                });
        },
        setRankValue() {
            for(var i = 0; i < this.liste.length; i++) {
                // attribution du rang à chaque joueur
                if (i == 0) {
                    this.liste[i].NoJoueur = 1;
                    this.place++;
                    this.atSamePlace++;
                }else{
                    if (this.liste[i].NbVictoires == this.liste[i-1].NbVictoires) {
                        this.liste[i].NoJoueur = this.liste[i-1].NoJoueur;
                        this.atSamePlace++;
                    }else{
                        this.liste[i].NoJoueur = this.place + this.atSamePlace;
                        this.place = this.place + this.atSamePlace;
                        this.atSamePlace = 1;
                    }
                }
                // initialisation des paliers pour les 3 premieres places
                if( this.first == -1) {
                    this.first = this.liste[i].NbVictoires;
                }else{
                    if (this.second == -1 && this.liste[i].NbVictoires != this.first) {
                        this.second = this.liste[i].NbVictoires;
                    }else{
                        if(this.second != -1 && this.third == -1 && this.liste[i].NbVictoires != this.second) {
                            this.third = this.liste[i].NbVictoires;
                        }
                    }
                }
            }
        },
        changeFirst(event) {
            this.first = event;
        },
        changeSecond(event) {
            this.second = event;
        },
        changeThird(event) {
            this.third = event;
        },
        isFirst(event) {
            return event == this.first;
        },
        isSecond(event) {
            return event == this.second;
        },
        isThird(event) {
            return event == this.third;
        }
    },
    created : function() {
        this.loadRank();
    }
};
</script>

<style>
.fas {
  margin-left: 10px;
}
.fas:hover {
  cursor: pointer;
}
.v-align {
  vertical-align: middle;
}
.list-enter-active,
.list-leave-active {
  transition: all 0.5s;
}
.list-enter.right,
.list-leave-to.right {
  opacity: 0;
  transform: translateX(30px);
}
.list-enter,
.list-leave-to {
  opacity: 0;
  transform: translateX(-30px);
}
</style>
