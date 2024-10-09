import { defineStore } from 'pinia'
import background from '~/services/background.service'
export default defineStore('background', {
  state: () => ({
    backgroundEffect: ''
  }),
  actions: {
    async nextBackgroundEffect () {
      const res = await background.nextBackgroundEffect()
      this.backgroundEffect = res['newValue']
    },
    async previousBackgroundEffect () {
      const res = await background.previousBackgroundEffect()
      this.backgroundEffect = res['newValue']
    }
  }
})
