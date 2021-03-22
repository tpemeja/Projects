import Vue from "vue";
import Vuex from "vuex";

Vue.use(Vuex);

export default new Vuex.Store({
    state: {
      username: "",
      nickname: ""
    },
    mutations: {
      SEARCH(state, username) {
        state.username = username;
    },
        displayProfile(state, nickname) {
      state.nickname = nickname;
    }
    },
    actions: {
      search(commit, username) {
        this.commit("SEARCH", username);
    },
        displayProfile(commit, nickname) {
      this.commit("displayProfile", nickname);
    }
    },
    getters: {
      username: function(state) {
        return state.username;
    },
    nickname: function(state) {
      return state.nickname;
    }
    }
});
