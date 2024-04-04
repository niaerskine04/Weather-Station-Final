<template class="bg-surface">
  <v-container  flat align="center">
    <v-row  flat  align="center" >
      <v-card class="bg-primary"  align="center" width="1400"   flat  >
        <v-card-item >
          <v-card-title class="text-h5 text-shadow font-weight-bold" align="center" justify="center"> N.A.E. LIVE WEATHER </v-card-title>
        </v-card-item>
      </v-card>
    </v-row>
    <v-row>
      <v-card class="bg-surface" align="center" width="1400" flat>
        <v-card-item >
          <v-card-title align="center" >...About this Page...</v-card-title>
          <v-card-subtitle align="center"> This page will display real time weather station data that reflects the surroundinf environment of the prototype</v-card-subtitle>
        </v-card-item>
      </v-card>
    </v-row>
    <!-- <v-row>
        <v-col cols="12">
          <v-responsive>
            <v-text-field
              v-model="message"
              label="Converter"
              type="number"
              variant="filled"
              clearable
              @click:append="covert_to_far"
            ></v-text-field>
          </v-responsive>
        </v-col>
      </v-row> -->
    <v-row class="row row2" max-width="1200" max-height="200">
      <v-col class="col col1" cols="4">
          <v-card class=" text-h4 bg-tertiary" width="300" height="200"  variant= "tonal" title="PRESSURE" >
            <v-col>
              <v-card-item>
                <span class="text-shadow ">{{ pressure }}</span>
              </v-card-item>
            </v-col>
            <v-col>
              <v-icon align="right" color="error"
            icon="mdi-tsunami" size="50"></v-icon>
            </v-col>
          </v-card>
      </v-col>
      
      <v-col class="col col2" cols="4" >
          <v-card height="200" class=" text-h4 bg-tertiary" width="300"   variant= "tonal" title="ALTITUDE" >
            <v-col>
              <v-card-item>
                <span class="text-shadow">{{ altitude }}</span>
              </v-card-item>
            </v-col>
            <v-col>
              <v-icon align="right" color="error"
            icon="mdi-trending-up" size="50"></v-icon>
            </v-col>
          </v-card>
      </v-col>
      <v-col class="col col3" cols="4">
        <v-card height="200" class=" text-h4 bg-tertiary" width="300"   variant= "tonal" title="SOIL MOISTURE" >
            <v-col>
              <v-card-item>
                <span class="text-shadow">{{ soilmoisture }}</span>
              </v-card-item>
            </v-col>
            <v-col>
              <v-icon align="right" color="error"
            icon="mdi-water-circle" size="50"></v-icon>
            </v-col>
          </v-card>
      </v-col>
    </v-row>
    <v-row>
      <v-col cols="4">
        <figure class="highcharts-figure">
          <div id="container3"></div>
        </figure>
      </v-col>
      <v-col cols="4">
        <figure class="highcharts-figure">
          <div id="container4"></div>
        </figure>
      </v-col>
      <v-col cols="4">
        <figure class="highcharts-figure">
          <div id="container5"></div>
        </figure>
      </v-col>
    </v-row>
    <v-spacer></v-spacer>
    <v-row >
      <v-col cols="2"></v-col>
      <v-col cols="8" align="center">
        <v-text-field class="rounded-lg" append-inner-icon="mdi-map-marker" style="background-color:pink" 
         label="Celcius to Farenheit Converter" type="input">
          <input id=pascal>
        </v-text-field>
        <v-btn class="text-shadow"  :disabled="!form"
          :loading="loading"
          style="background-color:pink"
          size="large"
          type="submit"
          variant="compact" block
          >Convert </v-btn>
      </v-col>
      <v-col cols="2"></v-col>
    </v-row>
    <div></div>
    <v-row class="row row3">
      <v-col class="col col1" cols="3">
        
          <v-card class=" text-h4 mb-2  bg-tertiary" width="250" height="200"  variant= "tonal" title="TEMPERATURE" >
            <v-col>
              <v-card-item>
                <span class="text-shadow">{{ temperature }}</span>
                <!-- <v-btn title="Convert" @click="Tempconvert()"></v-btn> -->
              </v-card-item>
            </v-col>
            <v-col>
              <v-icon align="right" color="error"
            icon="mdi-thermometer" size="50"></v-icon>
            </v-col>
          </v-card>
          <div></div>
          <v-card class=" text-h4 bg-tertiary" width="250" height="200" variant="tonal"  title="HEAT INDEX">
            <v-col>
              <v-card-item>
                <span class="text-shadow">{{ heatindex }}</span>
              </v-card-item>
            </v-col>
            <v-col>
              <v-icon align="right" color="error"
            icon="mdi-white-balance-sunny" size="50"></v-icon>
            </v-col>
          
          </v-card>
      </v-col>
      <v-col class="col col2" cols="9">
        <figure class="highcharts-figure">
          <div id="container1"></div>
        </figure>
      </v-col>
    </v-row>
    <v-row>
      <v-col class="col col1" cols="3">
        <v-card class=" text-h4 bg-tertiary" width="250" height="200" title="HUMIDITY">
          <v-col>
            <v-card-item>
              <span class="text-shadow">{{ humidity }}</span>
            </v-card-item>
          </v-col>
          <v-col>
              <v-icon align="right" color="error"
              icon="mdi-heat-wave" size="50"></v-icon>
          </v-col>
        </v-card>
      </v-col>
      <v-col class="col col2" cols="9">
        <figure class="highcharts-figure">
          <div id="container2"></div>
        </figure>
      </v-col>
    </v-row>
  </v-container>
</template>
<script setup>
/** JAVASCRIPT HERE */

// IMPORTS
import { ref,reactive,watch ,onMounted,onBeforeUnmount,computed } from "vue";  
import { useRoute ,useRouter } from "vue-router";
import { useMqttStore } from '@/store/mqttStore'; // Import Mqtt Store
import { storeToRefs } from "pinia";

import Highcharts from "highcharts";
import more from "highcharts/highcharts-more";
import Exporting from "highcharts/modules/exporting";
Exporting(Highcharts);
more(Highcharts); 
 
// VARIABLES
const router      = useRouter();
const route       = useRoute();    
const Mqtt        = useMqttStore();
const { payload, payloadTopic } = storeToRefs(Mqtt);
const points = ref(10); // Specify the quantity of points to be shown on the live graph simultaneously.
const shift = ref(false); // Delete a point from the left side and append a new point to the right side of the graph.
const tempHiChart = ref(null); // Chart object
const humChart = ref(null); // Chart object -->
const presChart= ref(null); //pressure chart object
const altChart=ref(null);
const soilChart= ref(null);

var Tempstate=0;


//COMPUTED
const temperature = computed(() => {
  if (!!payload.value) {
    if(Tempstate==1){
      temperature=(temp*9/5)+32
      return  `${payload.value.temperature.toFixed(2)} °F`;
    }
    else{
      return `${payload.value.temperature.toFixed(2)} °C`;
    }
  }
});
const heatindex = computed(() => {
  if (!!payload.value) {
    return `${payload.value.heatindex.toFixed(2)} °C`;
  }
});
const humidity = computed(() => {
  if (!!payload.value) {
    return `${payload.value.humidity.toFixed(2)} %`;
  }
});

const pressure = computed(() => {
  if (!!payload.value) {
    return `${payload.value.pressure.toFixed(2)} Pa`;
  }
});
const altitude = computed(() => {
  if (!!payload.value) {
    return `${payload.value.altitude.toFixed(2)} m `;
  }
});

const soilmoisture = computed(() => {
  if (!!payload.value) {
    return `${payload.value.soilmoisture.toFixed(2)} %`;
  }
});

// const Tempconvert = async () => {
//     if(Tstate == 0){
//         Tstate = 1;
//     }
//     else{
//         Tstate = 0;
//     }
// };

// FUNCTIONS
onMounted(()=>{
    // THIS FUNCTION IS CALLED AFTER THIS COMPONENT HAS BEEN MOUNTED
    CreateCharts();
    CreateCharts1();
    CreateCharts2();
    CreateCharts3();
    CreateCharts4();
    reloadtime();
    Mqtt.connect();
    setTimeout(() => {
        // subscribes to the relevant topics 
        Mqtt.subscribe("620155827");
        Mqtt.subscribe("620155827_pub");
    }, 3000);
});


onBeforeUnmount(()=>{
    // THIS FUNCTION IS CALLED RIGHT BEFORE THIS COMPONENT IS UNMOUNTED
    Mqtt.unsubcribeAll();
});

// convert_to_far(()=>{
//   far= (input*9/5)+32;
//   print(far);
// });

function reloadtime(){
  setInterval( function() {
  window.location.reload();
}, 30000);
}

// const PressureConvert= async()=>{
//   if(Pstate == 0){
//         Pstate = 1;
//     }
//     else{
//         Pstate = 0;
//     }
// }
const CreateCharts = async () => {
  // TEMPERATURE CHART
  tempHiChart.value = Highcharts.chart("container1", {
    chart: { zoomType: "x" },
    title: { text: "Air Temperature and Heat Index Live Analysis", align: "left" },
    yAxis: {
      title: {
        text: "Air Temperature & Heat Index",
        style: { color: "#000000" },
      },
      labels: { format: "{value} °C" },
    },
    xAxis: {
      type: "datetime",
      title: { text: "Time", style: { color: "#000000" } },
    },
    tooltip: { shared: true },
    series: [
      {
        name: "Temperature",
        type: "spline",
        data: [],
        turboThreshold: 0,
        color: Highcharts.getOptions().colors[0],
      },
      {
        name: "Heat Index",
        type: "spline",
        data: [],
        turboThreshold: 0,
        color: Highcharts.getOptions().colors[1],
      },
    ],
  });
};

const CreateCharts1 = async () => {
  // Humidity CHART
  humChart.value = Highcharts.chart("container2", {
    chart: { zoomType: "x" },
    title: { text: "Humidity Live Analysis", align: "left" },
    yAxis: {
      title: {
        text: "Humidity",
        style: { color: "#000000" },
      },
      labels: { format: "{value} %" },
    },
    xAxis: {
      type: "datetime",
      title: { text: "Time", style: { color: "#000000" } },
    },
    tooltip: { shared: true },
    series: [
      {
        name: "Humidity",
        type: "spline",
        data: [],
        turboThreshold: 0,
        color: Highcharts.getOptions().colors[0],
      },
    ],
  });
};

const CreateCharts2= async () => {
  // Humidity CHART
  presChart.value = Highcharts.chart("container3", {
    chart: { zoomType: "x" },
    title: { text: "Pressure Live Analysis", align: "left" },
    yAxis: {
      title: {
        text: "Pressure",
        style: { color: "#000000" },
      },
      labels: { format: "{value} Pa" },
    },
    xAxis: {
      type: "datetime",
      title: { text: "Time", style: { color: "#000000" } },
    },
    tooltip: { shared: true },
    series: [
      {
        name: "Pressure",
        type: "spline",
        data: [],
        turboThreshold: 0,
        color: Highcharts.getOptions().colors[0],
      },
    ],
  });
};

const CreateCharts3 = async () => {
  // Humidity CHART
  altChart.value = Highcharts.chart("container4", {
    chart: { zoomType: "x" },
    title: { text: "Altitude Live Analysis", align: "left" },
    yAxis: {
      title: {
        text: "Altitude",
        style: { color: "#000000" },
      },
      labels: { format: "{value} m" },
    },
    xAxis: {
      type: "datetime",
      title: { text: "Time", style: { color: "#000000" } },
    },
    tooltip: { shared: true },
    series: [
      {
        name: "Altitude",
        type: "spline",
        data: [],
        turboThreshold: 0,
        color: Highcharts.getOptions().colors[0],
      },
    ],
  });
};

const CreateCharts4 = async () => {
  // Humidity CHART
  soilChart.value = Highcharts.chart("container5", {
    chart: { zoomType: "x" },
    title: { text: "Soil Moisture Live Analysis", align: "left" },
    yAxis: {
      title: {
        text: "Soil Moisture",
        style: { color: "#000000" },
      },
      labels: { format: "{value} %" },
    },
    xAxis: {
      type: "datetime",
      title: { text: "Time", style: { color: "#000000" } },
    },
    tooltip: { shared: true },
    series: [
      {
        name: "Soil Moisture",
        type: "spline",
        data: [],
        turboThreshold: 0,
        color: Highcharts.getOptions().colors[0],
      },
    ],
  });
};

const updateconvert= async () =>{

}

//WATCHERS
watch(payload,(data)=> {
    if(points.value > 0){ points.value -- ; }
    else{ shift.value = true; }

 tempHiChart.value.series[0].addPoint({y:parseFloat(data.temperature.toFixed(2)) ,x: data.timestamp * 1000 },
true, shift.value);

 tempHiChart.value.series[1].addPoint({y:parseFloat(data.heatindex.toFixed(2)) ,x: data.timestamp * 1000 },
true, shift.value);

humChart.value.series[0].addPoint({y:parseFloat(data.humidity.toFixed(2)) ,x: data.timestamp * 1000 },
true, shift.value);

presChart.value.series[0].addPoint({y:parseFloat(data.pressure.toFixed(2)) ,x: data.timestamp * 1000 },
true, shift.value);

altChart.value.series[0].addPoint({y:parseFloat(data.altitude.toFixed(2)) ,x: data.timestamp * 1000 },
true, shift.value);

soilChart.value.series[0].addPoint({y:parseFloat(data.soilmoisture.toFixed(2)) ,x: data.timestamp * 1000 },
true, shift.value);



})
</script>


<style scoped>
/** CSS STYLE HERE */

Figure {
  border: 2px solid black;
}

</style>
  