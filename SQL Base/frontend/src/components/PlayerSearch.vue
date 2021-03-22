<template>
    <div>
    <template v-if="getPlayerExistence()">
        <b-col cols="12">
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
            <b-list-group-item v-for="player in playerList" v-bind:key="player.NoJoueur">
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
    </template>
    <template v-else>
        <b-col cols="6">
            Impossible de trouver: {{this.playerName}}
        </b-col>
    </template>
</div>
</template>

<script>
import axios from "axios";
import store from "../store";
import router from "../router";



export default {
    data(){
     return{
         playerName: "",
         playerInfo: Object,
         playerExist: false,
         playerList: []
    }
},
    methods: {
        getPlayerInfo: function(event) {
            axios
                .get("http://localhost:3000/players/for/pseudo/" + this.playerName)
                .then(response => {
                    this.playerList = response.data;
                    this.playerExist = true;
                })
                .catch(e => {
                    this.playerInfo = {};
                    this.playerExist = false;
                })
        },
        getPlayerName: function() {
            this.playerName = this.$store.getters.username;
            this.getPlayerInfo();
        },
        getPlayerExistence: function() {
            return this.playerExist;
        },
        redirectProfile: function(nickname) {
            this.$store.dispatch("displayProfile",nickname);
            this.$router.push("/playerProfile");
        }
    },
    created: function() {
        this.getPlayerName();
    }
};
</script>

<style>
.button {
  border: none;
  border-radius: 2px;
}

.button-close {
  background-color: white;
}
</style>
