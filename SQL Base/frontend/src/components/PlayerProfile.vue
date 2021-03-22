<template>
    <div class="v-align">
        <b-col cols="12">
            <b-list-group-item variant="success">
                <b-row>
                    <b-col cols="3">
                        Pseudo
                    </b-col>
                    <b-col cols="3">
                        Nom
                    </b-col>
                    <b-col cols="3">
                        Prénom
                    </b-col>
                    <b-col cols="2">
                        W/L (Ratio)
                    </b-col>
                </b-row>
            </b-list-group-item>
            <b-list-group-item>
                <b-row>
                    <b-col cols="3">
                        {{nickname}}
                    </b-col>
                    <b-col cols="3">
                        {{surname}}
                    </b-col>
                    <b-col cols="3">
                        {{name}}
                    </b-col>
                    <b-col cols="2">
                        {{winNumber}}/{{loseNumber}} ({{winRate}})
                    </b-col>
                </b-row>
            </b-list-group-item>
            <b-list-group-item>
                <b-row>
                    <b-col cols="3">
                        Nombre de carte(s): {{cardQuantity}}
                    </b-col>
                    <b-col cols="3">
                        Nombre de rares: {{collectionRarity}}
                    </b-col>
                    <br />
                    <b-col cols="3">
                        Valeur de la collection: {{collectionValue}}$
                    </b-col>
                </b-row>
                    <br />
                    <b-col cols="3">
                        Decks:
                    </b-col>
                    <b-list-group-item variant="info">
                        <b-row>
                        <b-col cols="1">
                            Numéro
                        </b-col>
                        <b-col cols="4">
                            Titre
                        </b-col>
                        <b-col cols="6">
                            Description
                        </b-col>
                    </b-row>
                    </b-list-group-item>
                    <b-list-group-item v-for="deck in deckList" v-bind:key="deck.NoDeck">
                        <b-row>
                        <b-col cols="1">
                            {{deck.NoDeck}}
                        </b-col>
                        <b-col cols="4">
                            {{deck.Titre}}
                        </b-col>
                        <b-col cols="6">
                            {{deck.Description}}
                        </b-col>
                    </b-row>
                    <cards-in-deck v-bind:noDeck="deck.NoDeck"></cards-in-deck>
                    </b-list-group-item>
            </b-list-group-item>
      </b-col>
</div>
</template>

<script>
import axios from "axios";
import CardsInDeck from "./CardsInDeck.vue";
import store from "../store";

export default {
    components: {
        CardsInDeck
    },
    data(){
     return{
         playerId: "",
         nickname: "Gougeon",
         surname: "",
         name: "",
         winNumber: 0,
         loseNumber: 0,
         gamesPlayed: 0,
         winRate: 0,
         cardQuantity: "0",
         collectionValue: "0",
         collectionRarity: "0",
         deckList: []
    }
},
    methods: {
        loadValue: function(event) {
            axios
                .get("http://localhost:3000/players/compute/collection/value/" + this.playerId)
                .then(response => {
                    if (response.data.length != 0) {
                        this.collectionValue = response.data[0].ValeurJoueur;
                    }
                })
                .catch(e => {
                    console.error(e);
                });
        },
        loadRarity: function(event) {
            axios
                .get("http://localhost:3000/players/compute/collection/rarity/" + this.playerId)
                .then(response => {
                    if (response.data.length != 0) {
                        this.collectionRarity = response.data[0].NbCartesRares;
                    }
                })
                .catch(e => {
                    console.error(e);
                });
        },
        loadProfile: function(event) {
            axios
                .get("http://localhost:3000/players/for/pseudo/" + this.nickname)
                .then(response => {
                    this.playerId = response.data[0].NoJoueur;
                    this.surname = response.data[0].Nom;
                    this.name = response.data[0].Prenom;
                    this.loadValue();
                    this.loadRarity();
                    this.loadGames();
                    this.loadCardQuantity();
                    this.loadDecks();
                })
                .catch(e => {
                    console.error(e);
                });
        },
        loadGames: function(event) {
            axios
                .get("http://localhost:3000/players/compute/games/played/" + this.playerId)
                .then(response => {
                    if (response.data[0].NbParties != 0) {
                        this.gamesPlayed = response.data[0].NbParties;
                        this.loadWonGames();
                    }else{
                        this.winRate = "undefined";
                    }
                })
                .catch(e => {
                    console.error(e);
                });
        },
        loadWonGames: function(event) {
            axios
                .get("http://localhost:3000/players/compute/games/won/" + this.playerId)
                .then(response => {
                    if (response.data.length != 0) {
                        this.winNumber = response.data[0].NbVictoires;
                        this.computeLoseNumber();
                    }
                })
                .catch(e => {
                    console.error(e);
                });
        },
        loadCardQuantity: function(event) {
            axios
                .get("http://localhost:3000/players/compute/cards/quantity/" + this.playerId)
                .then(response => {
                    if (response.data.length != 0) {
                        this.cardQuantity = response.data[0].NbCartes;
                    }
                })
                .catch(e => {
                    console.error(e);
                });
        },
        loadDecks: function(event) {
            axios
                .get("http://localhost:3000/decks/for/player/" + this.playerId)
                .then(response => {
                    if (response.data.length != 0) {
                        this.deckList = response.data;
                    }
                })
                .catch(e => {
                    console.error(e);
                });
        },
        computeWinRate: function(event) {
            this.winRate = (Math.round((parseInt(this.winNumber,10) /parseInt(this.gamesPlayed,10)) * 100)).toString(10) + "%";
        },
        computeLoseNumber: function(event) {
            this.loseNumber = parseInt(this.gamesPlayed,10) - parseInt(this.winNumber,10);
            this.computeWinRate();
        }
    },
    created : function() {
        this.nickname = this.$store.getters.nickname;
        this.loadProfile();
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
</style>
