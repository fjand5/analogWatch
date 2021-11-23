let socket = WebSocket.prototype // 

const command = {
    state: () => ({
        data: {},
    }),
    mutations: {
        setData: function(state, data){
            state.data = {...state.data, ...JSON.parse(data)}
        }
    },
    actions: {
        initCommand: function(context){
            socket = new WebSocket('ws://'+window.location.host+':81');
            socket.addEventListener('message', function (event) {
                context.commit("setData",event.data);
            });
        },
        onDevice: function(context, id){
            let obj = {
                id,
                value: "true"
            }
            return socket.send(JSON.stringify(obj))
        },
        offDevice: function(context, id){
            let obj = {
                id,
                value: "false"
            }
            return socket.send(JSON.stringify(obj))
        },
        onSchedule: function(context, {id, hour, minute}){
            let obj = {
                id: "schedule-on-" + id,
                value: hour + ":"+minute,
            }
            return socket.send(JSON.stringify(obj))
        },
        offSchedule: function(context, {id, hour, minute}){
            let obj = {
                id: "schedule-off-" + id,
                value: hour + ":"+minute,
            }
            return socket.send(JSON.stringify(obj))
        }

    },
    getters: {
        getDeviceOn: function(state){
            let obj = state.data
            return (id)=>{
                let key = "schedule-on-" + id
                let data = obj[key]
                if (!data)
                    return undefined
                let hour = data.split(":")[0]
                let minute = data.split(":")[1]
                
                let time = new Date()
                time.setHours(hour)
                time.setMinutes(minute)
                return time
            }
        },
        getDeviceOff: function(state){
            let obj = state.data
            return (id)=>{
                let key = "schedule-off-" + id
                let data = obj[key]
                if (!data)
                    return undefined
                let hour = data.split(":")[0]
                let minute = data.split(":")[1]
                
                let time = new Date()
                time.setHours(hour)
                time.setMinutes(minute)
                return time
            }
        },
    }
  }
export default command
  