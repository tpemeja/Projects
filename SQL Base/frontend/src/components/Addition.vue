<template>
    <b-col cols="10">
        <b-row>
    Que voulez-vous ajouter:
    <select name="ajout" id="ajout" v-model="ajout" >
        <option value="card">carte</option>
        <option value="player">joueur</option>
        <option value="addDeck">deck</option>
        <option value="deck">carte dans un deck</option>
        <option value="addCardPlayer">carte pour un joueur</option>
    </select>
        ?
    </b-row>
    <div class="mx-auto mt-3" style="width: 300px">
        <template v-if="playerForm()">
    <b-form v-on:submit.prevent="addPlayer">
        <b-form-group>
            <b-form-input required type="text" id="surname" placeholder="Nom" v-model="surname"></b-form-input>
    </b-form-group>
    <b-form-group>
        <b-form-input required type="text" id="name" placeholder="Prénom" v-model="name"></b-form-input>
    </b-form-group>
        <b-form-group>
            <b-form-input required type="text" id="nickname" placeholder="Pseudonyme" v-model="nickname"></b-form-input>
        </b-form-group>
        <b-form-group>
            <b-button class="button button-close" type="submit">Ajouter !</b-button>
        </b-form-group>
    </b-form>
    </template>
    <template v-else>
        <template v-if="cardForm()">
            <b-form v-on:submit.prevent="addCard">
                <b-form-group>
                    <b-form-input required type="text" id="title" placeholder="Titre" v-model="title"></b-form-input>
                </b-form-group>
                <b-form-group>
                    <b-form-input required type="text" id="description" placeholder="Description" v-model="description"></b-form-input>
                </b-form-group>
                <b-form-group>
                    <b-form-input required type="text" id="type" placeholder="Type" v-model="type"></b-form-input>
                </b-form-group>
                <b-form-group>
                    <b-form-input required type="text" id="family" placeholder="Famille" v-model="family"></b-form-input>
                </b-form-group>
                <b-form-group label="Attaque:" label-for="attack">
                    <b-form-input required min="0" type="number" id="attack" placeholder="Attack" v-model="attack"></b-form-input>
                </b-form-group>
                <b-form-group label="Défense" label-for="defense">
                    <b-form-input required min="0" type="number" id="defense" placeholder="Defense" v-model="defense"></b-form-input>
                </b-form-group>
                <b-form-group>
                    <b-button class="button button-close" type="submit">Ajouter !</b-button>
                </b-form-group>
            </b-form>
        </template>
        <template v-else>
            <template v-if="deckForm()">
                Choissisez le deck :
                <select name="noDeck" id="noDeck" v-model="noDeck">
                    <option v-bind:value="deckId.NoDeck" v-for="deckId in deckList" v-bind:key="deckId.NoDeck">{{deckId.Titre}}</option>
                </select>
                <template v-if="deckSelected()">
                    <br />
                    Quel carte ajouter ?
                    <br />
                    <b-form v-on:submit.prevent="addCardInDeck">
                        <select name="noCard" id="noCard" v-model="noCard">
                            <option v-bind:value="card.NoCarte" v-for="card in cardList" v-bind:key="card.NoCarte">{{card.Titre}}</option>
                        </select>
                        <b-form-group label ="Nombre d'exemplaire(s):" label-for="cardNumber">
                            <b-form-input required type="number" min="1" id="cardNumber" v-model="cardNumber"></b-form-input>
                        </b-form-group>
                        <b-form-group>
                            <b-button class="button button-close" type="submit">Ajouter !</b-button>
                        </b-form-group>
                    </b-form>
                </template>
                <template v-else>
                </template>
            </template>
            <template v-else>
                <template v-if="cardPlayerForm()">
                    Choissisez le joueur :
                    <select name="noPlayer" id="noPlayer" v-model="noPlayer">
                        <option v-bind:value="player.NoJoueur" v-for="player in playerList" v-bind:key="player.NoJoueur">{{player.Pseudonyme}}</option>
                    </select>
                    <template v-if="playerSelected()">
                        <br />
                        Quel carte ajouter ?
                        <br />
                        <b-form v-on:submit.prevent="addCardForPlayer">
                            <select name="noCard" id="noCard" v-model="noCard">
                                <option v-bind:value="card.NoCarte" v-for="card in playerCards" v-bind:key="card.NoCarte">{{card.Titre}}</option>
                            </select>
                            <template v-if="cardSelected()">
                                <br />
                                Choissisez la version:
                                <br />
                                <select name="noVersion" id="noVersion" v-model="noVersion">
                                    <option v-bind:value="version.NoVersion" v-for="version in versionList" v-bind:key="version.NoVersion">{{version.DateImpression}} - {{version.Rendu}}</option>
                                </select>
                                <b-form-group>
                                    <b-form-input required type="text" id="acquisitionDate" placeholder="Date d'acquisition" v-model="acquisitionDate"></b-form-input>
                                </b-form-group>
                                <b-form-group>
                                    <b-form-input required type="text" id="price" placeholder="Prix" v-model="price"></b-form-input>
                                </b-form-group>
                                <b-form-group>
                                    <b-form-input required type="text" id="how" placeholder="Moyen d'obtention" v-model="how"></b-form-input>
                                </b-form-group>
                                <b-form-group>
                                    <b-form-input required type="text" id="state" placeholder="Etat (0: médiocre, 100: excellente)" v-model="state"></b-form-input>
                                </b-form-group>
                            <b-form-group label ="Nombre d'exemplaire(s):" label-for="cardNumber">
                                <b-form-input required type="number" min="1" id="cardNumber" v-model="cardNumber"></b-form-input>
                            </b-form-group>
                            <b-form-group>
                                <b-button class="button button-close" type="submit">Ajouter !</b-button>
                            </b-form-group>
                    </template>
                    <template v-else></template>
                </b-form>
                    </template>
                    <template v-else></template>
                </template>
                <template v-else>
                    <template v-if="addDeckForm()">
                <b-form v-on:submit.prevent="addDeck">
                    <b-form-group>
                        <b-form-input required type="text" id="title" placeholder="Titre" v-model="title"></b-form-input>
                </b-form-group>
                <b-form-group>
                    <b-form-input required type="text" id="description" placeholder="Description" v-model="description"></b-form-input>
                </b-form-group>
                    <b-form-group>
                        <b-button class="button button-close" type="submit">Ajouter !</b-button>
                    </b-form-group>
                </b-form>
                </template>
                <template v-else></template>
                </template>
            </template>
        </template>
    </template>
  </div>
 </b-col>
</template>

<script>
import axios from "axios";
import router from "../router";

export default {
  data() {
    return {
      ajout: "aucun",
      // player part
      surname: "",
      name: "",
      nickname: "",
      //card part
      title: "",
      description: "",
      type: "",
      family: "",
      attack: 0,
      defense: 0,
      //deck part
      deckList: [],
      noDeck: "",
      cardList: [], // card that are not in this deck
      noCard: "",
      cardNumber: 0,
      // add card for a player part
      playerCards: [],
      playerList: [],
      versionList: [],
      noVersion: "",
      noPlayer: "",
      acquisitionDate:"",
      how: "",
      price: "",
      state: ""
    };
  },
  methods: {
      cardForm: function() {
          return (this.ajout == "card");
      },
      playerForm: function() {
          return (this.ajout == "player");
      },
      deckForm: function() {
          return (this.ajout == "deck");
      },
      addDeckForm: function() {
          return (this.ajout == "addDeck");
      },
      cardPlayerForm: function() {
          return (this.ajout == "addCardPlayer");
      },
      deckSelected: function() {
          return (this.noDeck != "");
      },
      cardSelected: function() {
          return (this.noCard != "");
      },
      playerSelected: function() {
          return (this.noPlayer != "");
      },
      loadDecks: function(event) {
          axios
            .get("http://localhost:3000/decks/all")
            .then(response => {
                this.deckList = response.data;
            })
            .catch(e => {
                console.error(e);
            })
      },
      loadPlayers: function(event) {
          axios
            .get("http://localhost:3000/players/all")
            .then(response => {
                this.playerList = response.data;
            })
            .catch(e => {
                console.error(e);
            })
      },
      loadCardVersion: function() {
         axios
            .get("http://localhost:3000/cards/for/version/" + this.noCard)
            .then(response => {
                this.versionList = response.data;
            })
            .catch(e => {
                console.error(e);
            })
      },
      addCard: function(event) {
          axios
            .post("http://localhost:3000/cards/",{title: this.title,
                                                  description: this.description,
                                                  type: this.type,
                                                  family: this.family,
                                                  attack: this.attack,
                                                  defense: this.defense
            })
            .then(response => {
                console.log("Successfully added !");
                this.$router.push("/encyclopedia");
            })
            .catch(e => {
                console.log("Impossible to add this card");
                console.error(e);
            })
      },
      addCardForPlayer: function(event) {
          axios
            .post("http://localhost:3000/cardForPlayer/",{Date_Acquisition: this.acquisitionDate,
                                                  Moyen_Acquisition: this.how,
                                                  Prix: this.price,
                                                  NoJoueur: this.noPlayer,
                                                  NoCarte: this.noCard,
                                                  NoVersion: this.noVersion,
                                                  Etat: this.state,
                                                  NbExemplaires: this.cardNumber,
            })
            .then(response => {
                console.log("Successfully added !");
                this.$router.push("/encyclopedia");
            })
            .catch(e => {
                console.log("Impossible to add this card");
                console.error(e);
            })
      },
      addPlayer: function(event) {
          axios
            .post("http://localhost:3000/players/",{surname: this.surname,
                                                  name: this.name,
                                                  nickname: this.nickname
            })
            .then(response => {
                console.log("Successfully added !");
                this.$router.push("/players");
            })
            .catch(e => {
                console.log("Impossible to add this player");
                console.error(e);
            })
      },
      addDeck: function(event) {
          axios
            .post("http://localhost:3000/decks/",{Titre: this.title,
                                                  Description: this.description
            })
            .then(response => {
                console.log("Successfully added !");
                this.$router.push("/decks");
            })
            .catch(e => {
                console.log("Impossible to add this deck");
                console.error(e);
            })
      },
      addCardInDeck: function(event) {
          axios
            .post("http://localhost:3000/cardInDeck",{NoDeck: this.noDeck,
                                                  NoCarte: this.noCard,
                                                  NbExemplaires: this.cardNumber
            })
            .then(response => {
                console.log("Successfully added !");
                this.$router.push("/decks");
            })
            .catch(e => {
                console.log("Impossible to add this card in this deck");
                console.error(e);
            })
      }
  },
  watch: {
      ajout: function() {
          if (this.ajout == "deck") {
              this.loadDecks();
          }
          if (this.ajout == "addCardPlayer") {
              this.loadPlayers();
          }
      },
      noDeck: function() {
          axios
            .get("http://localhost:3000/cards/for/notInDeck/" + this.noDeck)
            .then(response => {
                this.cardList = response.data;
            })
            .catch(e => {
                console.error(e);
            })
      },
      noPlayer: function() {
          axios
            .get("http://localhost:3000/cards/for/notPossededBy/" + this.noPlayer)
            .then(response => {
                this.playerCards = response.data;
            })
            .catch(e => {
                console.error(e);
            })
      },
      noCard: function() {
          this.loadCardVersion();
      }
  }
};
</script>

<style scoped>
</style>
