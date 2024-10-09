import { defineStore } from 'pinia'
import command from '~/services/command.service'

export default defineStore('command', {
  state: () => ({}),
  actions: {
    async setCommandLearning (url) {
      await command.setCommandLearning(url)
    }
  }
})
