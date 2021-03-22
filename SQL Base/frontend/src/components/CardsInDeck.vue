<template>
    <div   class="v-align">
    <b-container>
            <b-col cols="13">
                <b-list-group-item variant="secondary">
                    <b-row>
                    <b-col cols="1">
                    {{field.NoCarte}}
                </b-col>
                <b-col cols="3">
                    {{field.Titre}}
                </b-col>
                <b-col cols="4">
                    {{field.Description}}
                </b-col>
                    <b-col cols="2">
                    {{field.Famille}}
                </b-col>
                    <b-col cols="1">
                    {{field.Attaque}}
                </b-col>
                    <b-col cols="1">
                    {{field.Defense}}
                </b-col>
                    <b-col cols="1">
                        {{field.NbExemplaires}}
                    </b-col>
                </b-row>
                </b-list-group-item>
          <b-list-group-item  v-for="card in cardList" v-bind:key="card.NoCarte">
              <b-row>
              <b-col cols="1">
              {{card.NoCarte}}
          </b-col>
          <b-col cols="3">
              {{card.Titre}}
          </b-col>
          <b-col cols="4">
              {{card.Description}}
          </b-col>
              <b-col cols="2">
              {{card.Famille}}
          </b-col>
              <b-col cols="1">
              {{card.Attaque}}
          </b-col>
              <b-col cols="1">
              {{card.Defense}}
          </b-col>
          <b-col cols="1">
              ({{card.NbExemplaires}})
          </b-col>
          </b-row>
        </b-list-group-item>
    </b-col>
</b-container>
</div>
</template>

<script>
import axios from "axios";

export default {
    props: ['noDeck'],
    data(){
     return{
         cardList: [],
         field: {NoCarte: "Numéro",
                 Titre: "Titre",
                 Description: "Description",
                 Type: "Type",
                 Famille: "Famille",
                 Attaque: "Attaque",
                 Defense: "Defense",
                 NbExemplaires: "(Nombre)"
     }
    }
},
    methods: {
        loadCards: function(event) {
            axios
                .get("http://localhost:3000/cards/for/deck/" + this.noDeck)
                .then(response => {
                    this.cardList = response.data;
                })
                .catch(e => {
                    console.error(e);
                });
        }
    },
    created : function() {
        this.loadCards();
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
