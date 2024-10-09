import { baseUrl } from '~/utlis'

const getLed = async () => {
  const data = await fetch(baseUrl + '/getLed')
  const json = await data.json()
  return json
}
const setPower = async power => {
  const data = await fetch(
    baseUrl +
      '/setPower?' +
      new URLSearchParams({
        value: power
      })
  )
  const json = await data.json()
  return json
}
const setAutoSyncTime = async auto => {
  const data = await fetch(
    baseUrl +
      '/setAutoSyncTime?' +
      new URLSearchParams({
        value: auto
      })
  )
  const json = await data.json()
  return json
}
const setDateTime = async timeStamp => {
  const data = await fetch(
    baseUrl +
      '/setDateTime?' +
      new URLSearchParams({
        value: timeStamp
      })
  )
  const json = await data.json()
  return json
}
const setBrightness = async brightness => {
  const data = await fetch(
    baseUrl +
      '/setBrightness?' +
      new URLSearchParams({
        value: brightness
      })
  )
  const json = await data.json()
  return json
}
const setSecondHandColor = async color => {
  const data = await fetch(
    baseUrl +
      '/setSecondHandColor?' +
      new URLSearchParams({
        value: color
      })
  )
  const json = await data.json()
  return json
}
const setMinuteHandColor = async color => {
  const data = await fetch(
    baseUrl +
      '/setMinuteHandColor?' +
      new URLSearchParams({
        value: color
      })
  )
  const json = await data.json()
  return json
}
const setHourHandColor = async color => {
  const data = await fetch(
    baseUrl +
      '/setHourHandColor?' +
      new URLSearchParams({
        value: color
      })
  )
  const json = await data.json()
  return json
}
export default {
  setPower,
  getLed,
  setBrightness,
  setSecondHandColor,
  setMinuteHandColor,
  setHourHandColor,
  setDateTime,
  setAutoSyncTime
}
