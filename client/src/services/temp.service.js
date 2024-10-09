import { baseUrl } from '~/utlis'

const getTemp = async () => {
  const data = await fetch(baseUrl + '/getTemp')
  const json = await data.json()
  return json
}

const setTempOffset = async offset => {
  const data = await fetch(
    baseUrl +
      '/setTempOffset?' +
      new URLSearchParams({
        value: offset
      })
  )
  const json = await data.json()
  return json
}
export default {
  getTemp,
  setTempOffset
}
