import { defineStore } from 'pinia'
import display from '~/services/display.service'
export default defineStore('display', {
  state: () => ({
    brightness: 0,
    power: false,
    backgroundEffect:""
  }),
  actions: {
    async loadDisplayData () {
      const displayData = await display.getDisplay()
      this.brightness = displayData['brightness']
      this.power = displayData['power']
    },
    async turnOnDisplay () {
      const res = await display.turnOnDisplay()
      this.power = res['newValue']
    },
    async turnOffDisplay () {
      const res = await display.turnOffDisplay()
      this.power = res['newValue']
    },
    async toggleDisplay () {
      let res
      if (this.power) res = await display.turnOffDisplay()
      else res = await display.turnOnDisplay()
      this.power = res['newValue']
    }
  }
})
