<template>
    <div   class="v-align">
    <b-container>
        <b-list-group-item variant="success">
            <b-col cols="13">
                    <b-row>
                    <b-col cols="1">
                    Numéro
                </b-col>
                <b-col cols="3">
                    Titre
                </b-col>
                <b-col cols="6">
                    Description
                </b-col>
                    <b-col cols="2">
                    Nombre de cartes différentes
                </b-col>
                </b-row>
            </b-col>
        </b-list-group-item>
        <b-list-group-item v-for="deck in deckList" v-bind:key="deck.NoDeck">
            <b-col cols="13">
                    <b-row>
                    <b-col cols="1">
                    {{deck.NoDeck}}
                </b-col>
                <b-col cols="3">
                    {{deck.Titre}}
                </b-col>
                <b-col cols="6">
                    {{deck.Description}}
                </b-col>
                    <b-col cols="2">
                    {{deck.NbCartes}}
                </b-col>
                </b-row>
            </b-col>
            <br />
            <b-col cols="3">
            Composition:
        </b-col>
        <br />
    <cards-in-deck v-bind:noDeck="deck.NoDeck"></cards-in-deck>
    </b-list-group-item>
</b-container>
</div>
</template>

<script>
import axios from "axios";
import CardsInDeck from "./CardsInDeck.vue";

export default {
    components: {
        CardsInDeck
    },
    data(){
     return{
         deckList: []
    }
},
    methods: {
        loadDecks: function(event) {
            axios
                .get("http://localhost:3000/decks/cardsQuantity")
                .then(response => {
                    this.deckList = response.data;
                })
                .catch(e => {
                    console.error(e);
                });
        }
    },
    created : function() {
        this.loadDecks();
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
