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


    timeColor: undefined,
    dayColor: undefined,
    lunarDayColor: undefined,

    timeShowTime: undefined,
    dayShowTime: undefined,
    lunarDayShowTime: undefined,

    
    autoSyncTime:undefined,
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

      // Đồng Hồ Số
      this.timeColor = res['timeColor']
      this.dayColor = res['dayColor']
      this.lunarDayColor = res['lunarDayColor']

      this.timeShowTime = res['timeShowTime']/1000
      this.dayShowTime = res['dayShowTime']/1000
      this.lunarDayShowTime = res['lunarDayShowTime']/1000
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
    },
    async setTimeColor (color) {
      const res = await led.setTimeColor(color)
      this.timeColor = res['newValue']
    },
    async setDayColor (color) {
      const res = await led.setDayColor(color)
      this.dayColor = res['newValue']
    },
    async setLunarDayColor (color) {
      const res = await led.setLunarDayColor(color)
      this.lunarDayColor = res['newValue']
    },
    async setTimeShowTime (time) {
      const res = await led.setTimeShowTime(time*1000)
      this.timeShowTime = res['newValue']/1000
    },
    async setDayShowTime (time) {
      const res = await led.setDayShowTime(time*1000)
      this.dayShowTime = res['newValue']/1000
    },
    async setLunarDayShowTime (time) {
      const res = await led.setLunarDayShowTime(time*1000)
      this.lunarDayShowTime = res['newValue']/1000
    }
  }
})
