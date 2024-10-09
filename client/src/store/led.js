import { timestamp } from '@vueuse/core'
import { defineStore } from 'pinia'
import led from '~/services/led.service'
export default defineStore('led', {
  state: () => ({
    power: undefined,
    brightness: undefined,
    secondHandColor: undefined,
    minuteHandColor: undefined,
    hourHandColor: undefined,
    timeStamp:undefined,
    autoSyncTime:undefined
  }),
  actions: {
    async getLed () {
      const res = await led.getLed()
      this.power = res['power']
      this.brightness = res['brightness']
      this.secondHandColor = res['secondHandColor']
      this.minuteHandColor = res['minuteHandColor']
      this.hourHandColor = res['hourHandColor']
      this.timeStamp = res['timeStamp']
      this.autoSyncTime = res['autoSyncTime']
    },
    async togglePower () {
      const res = await led.setPower(!this.power)
      this.power = res['newValue']
    },
    async setPower (power) {
      const res = await led.setPower(power)
      this.power = res['newValue']
    },
    async setAutoSyncTime (auto) {
      const res = await led.setAutoSyncTime(auto)
      this.autoSyncTime = res['newValue']
    },
    async setDateTime (timeStamp) {
      const res = await led.setDateTime(timeStamp)
      this.timeStamp = res['newValue']
    },
    async setBrightness (power) {
      const res = await led.setBrightness(power)
      this.brightness = res['newValue']
    },
    async setSecondHandColor (color) {
      const res = await led.setSecondHandColor(color)
      this.secondHandColor = res['newValue']
    },
    async setMinuteHandColor (color) {
      const res = await led.setMinuteHandColor(color)
      this.minuteHandColor = res['newValue']
    },
    async setHourHandColor (color) {
      const res = await led.setHourHandColor(color)
      this.hourHandColor = res['newValue']
    }
  }
})
