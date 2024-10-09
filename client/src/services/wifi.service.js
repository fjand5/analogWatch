import { baseUrl } from '~/utlis'

const scanWifi = async () => {
  const data = await fetch(baseUrl + '/scanWifi')
  const json = await data.json()
  return json
}
const getWifi = async () => {
  const data = await fetch(baseUrl + '/getWifi')
  const json = await data.json()
  return json
}

const setWifi = async ({apSSID, apPSK, staSSID, staPSK}) => {
  const wifi = {}
  apSSID && (wifi.apSSID = apSSID); 
  apPSK && (wifi.apPSK = apPSK); 
  staSSID && (wifi.staSSID = staSSID); 
  staPSK && (wifi.staPSK = staPSK); 

  const data = await fetch(
    baseUrl +
      '/setWifi?' +
      new URLSearchParams(wifi)
  )
  const json = await data.json()
  return json
}
export default {
  scanWifi,
  getWifi,
  setWifi
}
