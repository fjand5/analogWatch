<template>
  <div class="panel">
    <el-tabs value ="control">
    <el-tab-pane label="Điều khiển" name="control">
        <el-table
        :data="tableData"
        style="width: 90%">
        <el-table-column
            prop="name"
            label="Thiết bị"
            width="auto">  
        </el-table-column>
        <el-table-column
            label="Bật"
            width="auto">
            <template slot-scope="device">
                <el-button 
                    type="success"
                    @click="onDevice(device.row.id)"
                > Bật
                </el-button>
            </template>
        </el-table-column>
        <el-table-column
            label="Tắt"
            width="auto">
            <template slot-scope="device">
                <el-button 
                    type="danger"
                    @click="offDevice(device.row.id)"
                > Tắt
                </el-button>
            </template>
        </el-table-column>
        </el-table>
    </el-tab-pane>
    <el-tab-pane label="Hẹn giờ" name="schedule">
          <el-table
        :data="tableData">
        <el-table-column
            prop="name"
            label="Thiết bị"
            width="80px">  
        </el-table-column>
        <el-table-column
            label="Bật"
            width="auto">
            <template slot-scope="device">
                <el-time-picker
                :clearable="false"
                align="center"
                placeholder="Start time"
                v-model="device.row.onTime"
                format="HH:mm"
                :picker-options="{
                format: 'HH:mm'
                }"
                @change="onSchedule(device.row)"
                >
                </el-time-picker>
            </template>
        </el-table-column>
        <el-table-column
            label="Tắt"
            width="auto">
            <template slot-scope="device">
                <el-time-picker
                placeholder="Start time"
                v-model="device.row.offTime"
                format="HH:mm"
                :picker-options="{
                format: 'HH:mm'
                }"
                @change="offSchedule(device.row)"
                >
                </el-time-picker>
            </template>
        </el-table-column>
        </el-table>
    </el-tab-pane>
    </el-tabs>
  </div>
</template>

<script>
import {mapGetters} from 'vuex'
    export default {
      data() {
        return {
            tableData: [
            {
                name: 'Thiết bị 1',
                id: 'device1',
                onTime: undefined,
                offTime: undefined
            }, 
            {
                name: 'Thiết bị 2',
                id: 'device2',
                onTime: undefined,
                offTime: undefined
            }, 
            {
                name: 'Thiết bị 3',
                id: 'device3',
                onTime: undefined,
                offTime: undefined
            }, 
            {
                name: 'Thiết bị 4',
                id: 'device4',
                onTime: undefined,
                offTime: undefined
            }]
        }
      },
      computed:{
        ...mapGetters(['getDeviceOn','getDeviceOff'])
      },
      watch:{
        getDeviceOn: function(){
          for (let item of this.tableData) {
            item.onTime = this.getDeviceOn(item.id)
          }
        },
        getDeviceOff: function(){
          for (let item of this.tableData) {
            item.offTime = this.getDeviceOff(item.id)
          }
        },
      },
      methods:{
          onDevice: function(id){
              this.$store.dispatch("onDevice",id)
          },
          offDevice: function(id){
              this.$store.dispatch("offDevice",id)
          },
          onSchedule: function(device){
              this.$store.dispatch("onSchedule",{
                id: device.id,
                hour: device.onTime.getHours(),
                minute: device.onTime.getMinutes()
                })
          },
          offSchedule: function(device){
              this.$store.dispatch("offSchedule",{
                id: device.id,
                hour: device.offTime.getHours(),
                minute: device.offTime.getMinutes()
                })

          },
          
      }
    }
</script>

<style>
</style>