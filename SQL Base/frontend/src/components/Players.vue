<template>
    <div class="v-align">
    <b-container>
        <b-col cols="10">
            <b-list-group-item variant="info">
                <b-row>
                    <b-col cols="1">
                        Numéro
                    </b-col>
                    <b-col cols="3">
                        Pseudo
                    </b-col>
                    <b-col cols="3">
                        Nom
                    </b-col>
                    <b-col cols="3">
                        Prénom
                    </b-col>
                </b-row>
            </b-list-group-item>
          <b-list-group-item  v-for="player in list" v-bind:key="player.NoJoueur">
              <b-row>
              <b-col cols="1">
              {{player.NoJoueur}}
          </b-col>
          <b-col cols="3">
              <button v-on:click="redirectProfile(player.Pseudonyme)" class="button button-close"> {{player.Pseudonyme}} </button>
          </b-col>
          <b-col cols="3">
              {{player.Nom}}
          </b-col>
              <b-col cols="3">
              {{player.Prenom}}
          </b-col>
          </b-row>
        </b-list-group-item>
      </b-col>
</b-container>
</div>
</template>

<script>
import axios from "axios";
import router from "../router";
import store from "../store";

export default {
    data(){
     return{
         list: []
    }
},
    methods: {
        loadPlayers: function(event) {
            axios
                .get("http://localhost:3000/players/all")
                .then(response => {
                    this.list = response.data;
                })
                .catch(e => {
                    console.error(e);
                });
        },
        redirectProfile: function(nickname) {
            this.$store.dispatch("displayProfile",nickname);
            this.$router.push("/playerProfile");
        }
    },
    created : function() {
        this.loadPlayers();
    }
};
</script>

<style>
.fas {
  margin-left: 100px;
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

.button {
  border: none;
  border-radius: 2px;
}

.button-close {
  background-color: white;
}
</style>
