import { baseUrl } from '~/utlis'

const getDisplay = async () => {
  const data = await fetch(baseUrl + '/getDisplay')
  const json = await data.json()
  return json
}
const getValid = async () => {
  const data = await fetch(baseUrl + '/isValid')
  const json = await data.json()
  return json
}
const getMac = async () => {
  const data = await fetch(baseUrl + '/mac')
  const json = await data.json()
  return json
}
const setToken = async token => {
  const data = await fetch(
    baseUrl +
      '/setToken?' +
      new URLSearchParams({
        value: token
      })
  )
  const json = await data.json()
  return json
}
const setBrightness = async brightness => {
  const data = await fetch(
    baseUrl +
      '/setDisplayBrightness?' +
      new URLSearchParams({
        value: brightness
      })
  )
  const json = await data.json()
  return json
}
const setPanelType = async panelType => {
  const data = await fetch(
    baseUrl +
      '/setPanelType?' +
      new URLSearchParams({
        value: panelType
      })
  )
  const json = await data.json()
  return json
}
const setAutoBrightness = async autoMode => {
  const data = await fetch(
    baseUrl +
      '/setAutoBrightness?' +
      new URLSearchParams({
        value: autoMode ? 'true' : 'false'
      })
  )
  const json = await data.json()
  return json
}
const turnOnDisplay = async () => {
  const data = await fetch(
    baseUrl +
      '/turnOnDisplay'
  )
  const json = await data.json()
  return json
}
const turnOffDisplay = async () => {
  const data = await fetch(
    baseUrl +
      '/turnOffDisplay'
  )
  const json = await data.json()
  return json
}
export default {
  getDisplay,
  setBrightness,
  setAutoBrightness,
  turnOnDisplay,
  turnOffDisplay,
  getValid,
  getMac,
  setToken,
  setPanelType
}
