import { defineStore } from 'pinia'
import wifi from '~/services/wifi.service'
export default defineStore('wifi', {
  state: () => ({
    nearWifi: [],
    STASSID: undefined,
    STAPSK: undefined,
    APSSID: undefined,
    APPSK: undefined,
    ip:undefined
  }),
  actions: {
    async getWifi () {
      const res = await wifi.getWifi()
      this.STASSID = res["STASSID"]
      this.STAPSK = res["STAPSK"]
      this.APSSID = res["APSSID"]
      this.APPSK = res["APPSK"]
      this.ip = res["ip"]
    },
    async setWifi ({apSSID, apPSK, staSSID, staPSK}) {
      const res = await wifi.setWifi({apSSID, apPSK, staSSID, staPSK})
      this.STASSID = res["newValue"]["STASSID"]
      this.STAPSK = res["newValue"]["STAPSK"]
      this.APSSID = res["newValue"]["APSSID"]
      this.APPSK = res["newValue"]["APPSK"]
      this.ip = res["newValue"]["ip"]
    },

    async scanWifi () {
      this.nearWifi = []
      this.nearWifi = await wifi.scanWifi()

      this.nearWifi = this.nearWifi.filter(wifi => {
        return wifi.ssid != this.STASSID
      }).sort((a,b)=>b.rssi-a.rssi)
    }
  }
})
