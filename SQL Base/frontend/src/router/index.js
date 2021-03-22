import Vue from 'vue';
import Router from 'vue-router';

import Home from '../components/Home.vue';
import CardProfile from '../components/CardProfile.vue';
import DeckProfile from '../components/DeckProfile.vue';
import Encyclopedia from '../components/Encyclopedia.vue';
import PlayerProfile from '../components/PlayerProfile.vue';
import PlayerSearch from '../components/PlayerSearch.vue';
import Ranking from '../components/Ranking.vue';
import Players from '../components/Players.vue';
import Addition from '../components/Addition.vue';
import Decks from '../components/Decks.vue';

Vue.use(Router)

export default new Router({
    routes: [
        { path: '/', name: 'Home', component: Home },
        { path: '/card', name: 'CardProfile', component: CardProfile },
        { path: '/deck', name: 'DeckProfile', component: DeckProfile },
        { path: '/encyclopedia', name: 'Encyclopedia', component: Encyclopedia },
        { path: '/playerprofile', name: 'PlayerProfile', component: PlayerProfile },
        { path: '/search', name: 'PlayerSearch', component: PlayerSearch },
        { path: '/players', name: 'Players', component: Players },
        { path: '/ranking', name: 'Ranking', component: Ranking },
        { path: '/addition', name: 'Addition', component: Addition },
        { path: '/decks', name: 'Decks', component: Decks }
    ]
})
