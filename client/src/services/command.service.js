import { baseUrl } from '~/utlis'
const setCommandLearning = async url => {
  const data = await fetch(baseUrl + url)
  const json = await data.json()
  return json
}
export default { setCommandLearning }
