 <template>
    <VContainer class="container"  fluid color="surface"  >
        <VRow class="pd-1" max-width="1200px" >
            <VCol class="col col1" cols="12">
                  <v-card color="primary" variant="compact">
                      <p class="text-h6 ">Enter date range for Analysis</p>
                      <v-icon align="right" color="shadow" icon="mdi-weather-cloudy-clock" size="50"></v-icon>
                      <div></div>
                      <v-text-field v-model="start" label="Start Date" type="Date" density="compact" variant="solo-inverted" style="max-width: 300px" flat></v-text-field>
                      <v-text-field  v-model="end" label="End date" type="Date" density="compact" variant="solo-inverted" style="max-width: 300px" flat></v-text-field>
                      <VSpacer></VSpacer>
                      <VBtn class="text-caption" text="Analyze" @click="updateLineCharts(); updateCards(); updateHistogramCharts(); updateScatter();" color="primary" variant="tonal"></VBtn>
                </v-card>
              </VCol>    
        </VRow>
        <VRow class="row row2" max-width="1200px">
            <VCol class="col col1" cols="5">
                <figure class="highcharts-figure">
                    <div id="container" ></div>
                </figure>
            </VCol>
            <VCol class="col col2" cols="5">
                <figure class="highcharts-figure">
                    <div id="container0"></div>
                </figure>
            </VCol>
            <VCol class="col col2" cols="2" align="center">
                <VCard title="Temperature" width="160" variant="outlined" style="background-color:hotpink" density="compact" rounded="lg">
                    <VCardItem >
                        <VChipGroup class=" d-flex flex-row justify-center" size="compact" color="primaryContainer" variant="flat">
                            <VTooltip text="Min" location="start" >
                              <template v-slot:activator="{ props }">
                                <v-chip v-bind="props">{{ temperature.min }}</v-chip>
                              </template>
                            </VTooltip>
                            <VTooltip text="Range" location="top">
                              <template v-slot:activator="{ props }">
                                <v-chip v-bind="props">{{ temperature.range }}</v-chip>
                              </template>
                            </VTooltip>
                            <VTooltip text="Max" location="end">
                              <template v-slot:activator="{ props }">
                                <v-chip v-bind="props">{{ temperature.max }}</v-chip>
                              </template>
                            </VTooltip>
                        </VChipGroup>
                    </VCardItem>
                    <VCardItem align="center">
                        <span class="text-h3 text-shadow">{{ temperature.avg }}</span>
                    </VCardItem>
                </VCard>
               <div></div>
                <VCard title="Heat Index" width="160" variant="outlined" style="background-color:hotpink" density="compact" rounded="lg">
                    <VCardItem >
                        <VChipGroup class=" d-flex flex-row justify-center" size="compact" color="primaryContainer" variant="flat">
                            <VTooltip text="Min" location="start" >
                              <template v-slot:activator="{ props }">
                                <v-chip v-bind="props">{{ heatindex.min }}</v-chip>
                              </template>
                            </VTooltip>
                            <VTooltip text="Range" location="top">
                              <template v-slot:activator="{ props }">
                                <v-chip v-bind="props">{{ heatindex.range }}</v-chip>
                              </template>
                            </VTooltip>
                            <VTooltip text="Max" location="end">
                              <template v-slot:activator="{ props }">
                                <v-chip v-bind="props">{{ heatindex.max }}</v-chip>
                              </template>
                            </VTooltip>
                        </VChipGroup>
                    </VCardItem>
                    <VCardItem align="center">
                        <span class="text-h3 text-shadow" >{{ heatindex.avg }}</span>
                    </VCardItem>
                </VCard>
            </VCol>
        </VRow>
        <VRow>
          <VCol class="col col3" cols="2" align="center">
                <VCard title="Humidity" width="160" variant="outlined" color="primary" density="compact" rounded="lg">
                    <VCardItem class="mb-n5">
                        <VChipGroup class="d-flex flex-row justify-center" color="primaryContainer" variant="flat">
                            <VTooltip text="Min" location="start" >
                              <template v-slot:activator="{ props }">
                                <v-chip v-bind="props">{{ humidity.min }}</v-chip>
                              </template>
                            </VTooltip>
                            <VTooltip text="Range" location="top" >
                              <template v-slot:activator="{ props }">
                                <v-chip v-bind="props">{{ humidity.range }}</v-chip>
                              </template>
                            </VTooltip>
                            <VTooltip text="Max" location="end">
                              <template v-slot:activator="{ props }">
                                <v-chip v-bind="props">{{ humidity.max }}</v-chip>
                              </template>
                            </VTooltip>
                        </VChipGroup>
                    </VCardItem>
                    <VCardItem align="center">
                        <span class="text-h3 text-primary ">{{ humidity.avg }}</span>
                    </VCardItem>
                </VCard>
            </VCol>
            <VCol class="col col2" cols="5">
                <figure class="highcharts-figure">
                    <div id="container1" ></div>
                </figure>
            </VCol>
            <VCol class="col col3" cols="5">
                <figure class="highcharts-figure">
                    <div id="container2"></div>
                </figure>
            </VCol>
        </VRow>
        <VRow max-width="1200px">
          <VCol class="col col1" cols="12" br>
            <figure class="highcharts-figure">
                <div id="container3"></div>
            </figure>
          </VCol>
        </VRow>
        <VRow class="row row4" max-width="1200px">
            <VCol class="col col1" cols="12" br >
                <figure class="highcharts-figure">
                    <div id="container4"></div>
                </figure>
            </VCol>
        </VRow>
        <VRow>
          <VCol class="col col3" cols="2" align="center">
            <VCard title="Pressure" width="160" variant="outlined" style="background-color:lavender" color="#000000" density="compact" rounded="lg">
                    <VCardItem class="mb-n2">
                        <VChipGroup class="d-flex flex-row justify-center" color="primaryContainer" variant="flat">
                            <VTooltip text="Min" location="start" >
                              <template v-slot:activator="{ props }">
                                <v-chip v-bind="props">{{ pressure.min }}</v-chip>
                              </template>
                            </VTooltip>
                            <VTooltip text="Range" location="top" >
                              <template v-slot:activator="{ props }">
                                <v-chip v-bind="props">{{ pressure.range }}</v-chip>
                              </template>
                            </VTooltip>
                            <VTooltip text="Max" location="end">
                              <template v-slot:activator="{ props }">
                                <v-chip v-bind="props">{{ pressure.max }}</v-chip>
                              </template>
                            </VTooltip>
                        </VChipGroup>
                    </VCardItem>
                    <VCardItem align="center">
                        <span class="text-h3 text-shadow ">{{ pressure.avg }}</span>
                    </VCardItem>
                </VCard>
                <VCard title="Altitude" width="160" variant="outlined" style="background-color: lavender" density="compact" rounded="lg">
                    <VCardItem class="mb-n2">
                        <VChipGroup class="d-flex flex-row justify-center" color="primaryContainer" variant="flat">
                            <VTooltip text="Min" location="start" >
                              <template v-slot:activator="{ props }">
                                <v-chip v-bind="props">{{ altitude.min }}</v-chip>
                              </template>
                            </VTooltip>
                            <VTooltip text="Range" location="top" >
                              <template v-slot:activator="{ props }">
                                <v-chip v-bind="props">{{ altitude.range }}</v-chip>
                              </template>
                            </VTooltip>
                            <VTooltip text="Max" location="end">
                              <template v-slot:activator="{ props }">
                                <v-chip v-bind="props">{{ altitude.max }}</v-chip>
                              </template>
                            </VTooltip>
                        </VChipGroup>
                    </VCardItem>
                    <VCardItem align="center">
                        <span class="text-h3 text-primary ">{{ altitude.avg }}</span>
                    </VCardItem>
                </VCard>
            </VCol>
            <VCol class="col col2" cols="5" br >
                <figure class="highcharts-figure">
                    <div id="container5"></div>
                </figure>
            </VCol>
            <VCol class=" col col3" cols="5" br>
              <figure class="highcharts-figure">
                    <div id="container6"></div>
              </figure>
            </VCol>
        </VRow>
        <VRow>
          <VCol class="col col1" cols="12" br >
                <figure class="highcharts-figure">
                    <div id="container7"></div>
                </figure>
          </VCol>
        </VRow>
        <VRow>
          <VCol class="col col1" cols="5" br >
                <figure class="highcharts-figure">
                    <div id="container8"></div>
                </figure>
          </VCol>
          <VCol class="col col2" cols="5" br >
                <figure class="highcharts-figure">
                    <div id="container9"></div>
                </figure>
          </VCol>
          <VCol class="col col3" cols="2">
            <VCard title="Soil M" width="160" variant="outlined" style="background-color:lightcyan" density="compact" rounded="lg">
                    <VCardItem class="mb-n2">
                        <VChipGroup class="d-flex flex-row justify-center" color="primaryContainer" variant="flat">
                            <VTooltip text="Min" location="start" >
                              <template v-slot:activator="{ props }">
                                <v-chip v-bind="props">{{ soilmoisture.min }}</v-chip>
                              </template>
                            </VTooltip>
                            <VTooltip text="Range" location="top" >
                              <template v-slot:activator="{ props }">
                                <v-chip v-bind="props">{{ soilmoisture.range }}</v-chip>
                              </template>
                            </VTooltip>
                            <VTooltip text="Max" location="end">
                              <template v-slot:activator="{ props }">
                                <v-chip v-bind="props">{{ soilmoisture.max }}</v-chip>
                              </template>
                            </VTooltip>
                        </VChipGroup>
                    </VCardItem>
                    <VCardItem align="center">
                        <span class="text-h3 text-primary ">{{ soilmoisture.avg }}</span>
                    </VCardItem>
                </VCard>
          </VCol>
        </VRow>
    </VContainer>
  </template> 


<script setup>
/** JAVASCRIPT HERE */

import Highcharts from "highcharts";
import more from "highcharts/highcharts-more";
import Exporting from "highcharts/modules/exporting";
import { withDirectives } from "vue";
Exporting(Highcharts);
more(Highcharts);

// IMPORTS
import { useMqttStore } from "@/store/mqttStore"; // Import Mqtt Store
import { storeToRefs } from "pinia";

import { useAppStore } from "@/store/appStore";
import {
  ref,
  reactive,
  watch,
  onMounted,
  onBeforeUnmount,
  computed,
} from "vue";
import { useRoute, useRouter } from "vue-router";

// VARIABLES
const Mqtt = useMqttStore();
const AppStore = useAppStore();
const router = useRouter();
const route = useRoute();
var start = ref(null);
var end = ref(null);
var temperature = reactive({ min: 0, max: 0, avg: 0, range: 0 });
var humidity = reactive({ min: 0, max: 0, avg: 0, range: 0 });
var heatindex = reactive({ min: 0, max: 0, avg: 0, range: 0 });
var pressure = reactive({ min: 0, max: 0, avg: 0, range: 0 });
var altitude = reactive({ min: 0, max: 0, avg: 0, range: 0 });
var soilmoisture = reactive({ min: 0, max: 0, avg: 0, range: 0 });

const tempHiLine = ref(null); // Chart object
const humLine = ref(null); // Chart object
const histo = ref(null); // Chart object
const tempHiScat = ref(null); // Chart object
const humScat = ref(null); // Chart object
const humtempspline= ref(null);
const pressLine=ref(null);
const altLine=ref(null);
const Altareaspline= ref(null);
const soilLine= ref(null);
const soilHumsspline=ref(null);
// FUNCTIONS

const CreateCharts = async () => {
  // TEMPERATURE CHART
  tempHiLine.value = Highcharts.chart("container", {
    chart: { zoomType: "x" },
    title: { text: "Air Temperature and Heat Index Analysis", align: "left" },
    subtitle: {
      text:
        " The heat index, also known as the apparent temperature, is a measure that combines air temperature and relative humidity to assess how hot it feels to the human body. " +
        "The relationship between heat index and air temperature is influenced by humidity levels. As humidity increases, the heat" +
        "index also rises, making the perceived temperature higher than the actual air temperature.",
    },
    yAxis: {
      title: {
        text: "Air Temperature & Heat Index",
        style: { color: "#000000" },
      },
      labels: { format: "{value} °C" },
    },

    tooltip: {
      pointFormat: "Heatindex: {point.x} °C <br/> Temperature: {point.y} °C",
    },
    xAxis: {
      type: "datetime",
      title: { text: "Time", style: { color: "#000000" } },
    },
    tooltip: { shared: true },
    series: [
      {
        name: "Temperature",
        type: "line",
        data: [],
        turboThreshold: 0,
        color: Highcharts.getOptions().colors[0],
      },
      {
        name: "Heat Index",
        type: "line",
        data: [],
        turboThreshold: 0,
        color: Highcharts.getOptions().colors[4],
      },
    ],
  });

  tempHiScat.value = Highcharts.chart("container0", {
    chart: { zoomType: "x" },
    title: {
      text: "Temperature & Heat Index Correlation Analysis",
      align: "left",
    },
    subtitle: {
      text: "Visualize the relationship between Temperature and Heat Index as well as revealing patterns or trends in the data",
    },
    yAxis: {
      title: {
        text: "Heat Index",
        style: { color: "#000000" },
      },
      labels: { format: "{value} °C" },
    },

    xAxis: {
      title: { text: "Temperature", style: { color: "#000000" } },
      labels: { format: "{value} °C" },
    },
    tooltip: {
      shared: true,
      pointFormat: "Temperature: {point.x} °C <br/> Heat Index: {point.y} °C",
    },
    series: [
      {
        name: "Analysis",
        type: "scatter",
        data: [],
        turboThreshold: 0,
        color: Highcharts.getOptions().colors[0],
      },
    ],
  });
  humLine.value = Highcharts.chart("container1", {
    chart: { zoomType: "x" },
    title: { text: "Humidity Analysis", align: "left" },
    yAxis: {
      title: {
        text: "Humidity",
        style: { color: "#000000" },
      },
      labels: { format: "{value} %" },
    },

    tooltip: {
      pointFormat: "Humidity: {point.x} % ",
    },
    xAxis: {
      type: "datetime",
      title: { text: "Time", style: { color: "#000000" } },
    },
    tooltip: { shared: true },
    series: [
      {
        name: "Humidity",
        type: "line",
        data: [],
        turboThreshold: 0,
        color: Highcharts.getOptions().colors[0],
      },
    ],
  });

  humScat.value = Highcharts.chart("container2", {
    chart: { zoomType: "x" },
    title: {
      text: "Humidity & Heat Index Correlation Analysis",
      align: "left",
    },
    subtitle: {
      text: "Visualize the relationship between Humidity and Heat Index as well as revealing patterns or trends in the data",
    },
    yAxis: {
      title: {
        text: "Heat Index",
        style: { color: "#000000" },
      },
      labels: { format: "{value} °C" },
    },

    xAxis: {
      title: { text: "Humidity", style: { color: "#000000" } },
      labels: { format: "{value} %" },
    },
    tooltip: {
      shared: true,
      pointFormat: "Humidity: {point.x} °C <br/> Heat Index: {point.y} °C",
    },
    series: [
      {
        name: "Analysis",
        type: "scatter",
        data: [],
        turboThreshold: 0,
        color: Highcharts.getOptions().colors[5],
      },
    ],
  });

  humtempspline.value = Highcharts.chart("container3", {
    chart: { zoomType: "x" },
    title: { text: "Temperature and Humidity Analysis", align: "left" },
    yAxis: {
      title: {
        text: "Temperature",
        style: { color: "#000000" },
      },
      labels: { format: "{value} %" },
    },

    xAxis: {
      title: { text: "Humidity", style: { color: "#000000" } },
      labels: { format: "{value} " },
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
        name: "Humidity",
        type: "spline",
        data: [],
        turboThreshold: 0,
        color: Highcharts.getOptions().colors[1],
      },
    ],
  });

  histo.value = Highcharts.chart("container4", {
    chart: { zoomType: "x" },
    title: { text: "Frequency Distribution Analysis", align: "left" },
    yAxis: {
      title: {
        text: "Frequency",
        style: { color: "#000000" },
      },
      labels: { format: "{value}" },
    },

    xAxis: {
      title: { text: "ID", style: { color: "#000000" } },
    },
    tooltip: { shared: true },
    series: [
      {
        name: "Temperature",
        type: "bar",
        data: [],
        turboThreshold: 0,
        color: Highcharts.getOptions().colors[0],
      },
      {
        name: "Humidity",
        type: "bar",
        data: [],
        turboThreshold: 0,
        color: Highcharts.getOptions().colors[1],
      },
      {
        name: "Heat Index",
        type: "bar",
        data: [],
        turboThreshold: 0,
        color: Highcharts.getOptions().colors[3],
      },
    ],
  });
  pressLine.value = Highcharts.chart("container5", {
    chart: { zoomType: "x" },
    title: { text: "Pressure Analysis", align: "left" },
    yAxis: {
      title: {
        text: "Pressure",
        style: { color: "#000000" },
      },
      labels: { format: "{value} Pa" },
    },

    tooltip: {
      pointFormat: "Pressure: {point.x} Pa ",
    },
    xAxis: {
      type: "datetime",
      title: { text: "Time", style: { color: "#000000" } },
    },
    tooltip: { shared: true },
    series: [
      {
        name: "Humidity",
        type: "line",
        data: [],
        turboThreshold: 0,
        color: Highcharts.getOptions().colors[0],
      },
    ],
  });

  altLine.value = Highcharts.chart("container6", {
    chart: { zoomType: "x" },
    title: { text: "Altitude Analysis", align: "left" },
    yAxis: {
      title: {
        text: "Altitude",
        style: { color: "#000000" },
      },
      labels: { format: "{value} m" },
    },

    tooltip: {
      pointFormat: "Altitude: {point.x} m ",
    },
    xAxis: {
      type: "datetime",
      title: { text: "Time", style: { color: "#000000" } },
    },
    tooltip: { shared: true },
    series: [
      {
        name: "Altitude",
        type: "line",
        data: [],
        turboThreshold: 0,
        color: Highcharts.getOptions().colors[6],
      },
    ],
  });

  Altareaspline.value = Highcharts.chart("container7", {
    chart: { zoomType: "x" },
    title: {
      text: "Pressure and Altitude Correlation Analysis",
      align: "left",
    },
    subtitle: {
      text: "Visualize the relationship between Pressure and Altitude as well as revealing patterns or trends in the data",
    },
    yAxis: {
      title: {
        text: "Pressure",
        style: { color: "#000000" },
      },
      labels: { format: "{value} Pa" },
    },

    xAxis: {
      title: { text: "Altitude", style: { color: "#000000" } },
      labels: { format: "{value} m" },
    },
    tooltip: {
      shared: true,
      pointFormat: "Pressure: {point.x} Pa <br/> Altitude: {point.y} m",
    },
    series: [
      {
        name: "Pressure",
        type: "areaspline",
        data: [],
        turboThreshold: 0,
        color: Highcharts.getOptions().colors[4],
      },
      {
        name: "Altitude",
        type: "areaspline",
        data: [],
        turboThreshold: 0,
        color: Highcharts.getOptions().colors[6],
      },
    ],
  });

  soilLine.value = Highcharts.chart("container8", {
    chart: { zoomType: "x" },
    title: { text: "Soil Moisture Analysis", align: "left" },
    yAxis: {
      title: {
        text: "Soil Moisture",
        style: { color: "#000000" },
      },
      labels: { format: "{value} %" },
    },

    tooltip: {
      pointFormat: "Soil Moisture: {point.x} % ",
    },
    xAxis: {
      type: "datetime",
      title: { text: "Time", style: { color: "#000000" } },
    },
    tooltip: { shared: true },
    series: [
      {
        name: "Soil Moisture",
        type: "line",
        data: [],
        turboThreshold: 0,
        color: Highcharts.getOptions().colors[4],
      },
    ],
  });

  soilHumsspline.value = Highcharts.chart("container9", {
    chart: { zoomType: "x" },
    title: {
      text: "Humidity and Soil Moisture Correlation Analysis",
      align: "left",
    },
    subtitle: {
      text: "Visualize the relationship between Humidity and Soil Moisture as well as revealing patterns or trends in the data",
    },
    yAxis: {
      title: {
        text: "Humidity",
        style: { color: "#000000" },
      },
      labels: { format: "{value} %" },
    },

    xAxis: {
      title: { text: "Soil Moisture", style: { color: "#000000" } },
      labels: { format: "{value} %" },
    },
    tooltip: {
      shared: true,
      pointFormat: "Humidity: {point.x} % <br/> Soil Moisture: {point.y} %",
    },
    series: [
      {
        name: "Humidity",
        type: "spline",
        data: [],
        turboThreshold: 0,
        color: Highcharts.getOptions().colors[5],
      },
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

onMounted(() => {
  // THIS FUNCTION IS CALLED AFTER THIS COMPONENT HAS BEEN MOUNTED
  Mqtt.connect(); // Connect to Broker located on the backend
  setTimeout(() => {
    // Subscribe to each topic
    Mqtt.subscribe("620155827");
    Mqtt.subscribe("620155827_sub");
  }, 3000);
  CreateCharts();
});

onBeforeUnmount(() => {
  // THIS FUNCTION IS CALLED RIGHT BEFORE THIS COMPONENT IS UNMOUNTED
  Mqtt.unsubcribeAll();
});

const updateLineCharts = async () => {
  if (!!start.value && !!end.value) {
    // Convert output from Textfield components to 10 digit timestamps
    let startDate = new Date(start.value).getTime() / 1000;
    let endDate = new Date(end.value).getTime() / 1000;
    // Fetch data from backend
    const data = await AppStore.getAllInRange(startDate, endDate);
    // Create arrays for each plot
    let temperature = [];
    let heatindex = [];
    let humidity = [];
    let pressure= [];
    let altitude= [];
    let soilmoisture= [];
    // Iterate through data variable and transform object to format recognized by highcharts
    data.forEach((row) => {
      temperature.push({
        x: row.timestamp * 1000,
        y: parseFloat(row.temperature.toFixed(2)),
      });
      heatindex.push({
        x: row.timestamp * 1000,
        y: parseFloat(row.heatindex.toFixed(2)),
      });
      humidity.push({
        x: row.timestamp * 1000,
        y: parseFloat(row.humidity.toFixed(2)),
      });
      pressure.push({
        x: row.timestamp * 1000,
        y: parseFloat(row.pressure.toFixed(2)),
      });
      altitude.push({
        x: row.timestamp * 1000,
        y: parseFloat(row.altitude.toFixed(2)),
      });
      soilmoisture.push({
        x: row.timestamp * 1000,
        y: parseFloat(row.soilmoisture.toFixed(2)),
      });

    });
    // Add data to Temperature and Heat Index chart
    tempHiLine.value.series[0].setData(temperature);
    tempHiLine.value.series[1].setData(heatindex);
    humLine.value.series[0].setData(humidity);
    pressLine.value.series[0].setData(pressure);
    soilLine.value.series[0].setData(soilmoisture);
    Altareaspline.value.series[0].setData(pressure);
    Altareaspline.value.series[1].setData(altitude);
    soilLine.value.series[0].setData(soilmoisture);
    soilHumsspline.value.series[0].setData(humidity);
    soilHumsspline.value.series[1].setData(soilmoisture);

  }
};

const updateCards = async () => {
  // Retrieve Min, Max, Avg, Spread/Range
  if (!!start.value && !!end.value) {
    // 1. Convert start and end dates collected fron TextFields to 10 digit timestamps
    let startDate = new Date(start.value).getTime() / 1000;
    let endDate = new Date(end.value).getTime() / 1000;
    // 2. Fetch data from backend by calling the API functions
    const temp = await AppStore.getTemperatureMMAR(startDate, endDate);
    const humid = await AppStore.getHumidityMMAR(startDate, endDate);
    const pres= await AppStore.getPressureMMAR(startDate, endDate);
    const alt= await AppStore.getAltitudeMMAR(startDate,endDate);
    const soil= await AppStore.getSoilMoistureMMAR(startDate, endDate);
    console.log(temp);
    temperature.max = temp[0].max.toFixed(1);
    temperature.min = temp[0].min.toFixed(1);
    temperature.avg = temp[0].avg.toFixed(1);
    temperature.range = temp[0].range.toFixed(1);
    humidity.max = humid[0].max.toFixed(1);
    humidity.min = humid[0].min.toFixed(1);
    humidity.avg = humid[0].avg.toFixed(1);
    humidity.range = humid[0].range.toFixed(1);
    pressure.max = pres[0].max.toFixed(1);
    pressure.min = pres[0].min.toFixed(1);
    pressure.avg = pres[0].avg.toFixed(1);
    pressure.range = pres[0].range.toFixed(1);
    altitude.max = alt[0].max.toFixed(1);
    altitude.min = alt[0].min.toFixed(1);
    altitude.avg = alt[0].avg.toFixed(1);
    altitude.range = alt[0].range.toFixed(1);
    soilmoisture.max = soil[0].max.toFixed(1);
    soilmoisture.min = soil[0].min.toFixed(1);
    soilmoisture.avg = soil[0].avg.toFixed(1);
    soilmoisture.range = soil[0].range.toFixed(1);
    


  }
};

const updateHistogramCharts = async () => {
  // Retrieve Min, Max, Avg, Spread/Range for Column graph
  let startDate = new Date(start.value).getTime() / 1000;
  let endDate = new Date(end.value).getTime() / 1000;
  if (!!start.value && !!end.value) {
    const temp = await AppStore.getFreqDistro(
      "temperature",
      startDate,
      endDate
    );
    const humid = await AppStore.getFreqDistro("humidity", startDate, endDate);
    const hi = await AppStore.getFreqDistro("heatindex", startDate, endDate);
    // 3. create an empty array for each variable (temperature, humidity and heatindex)
    // see example below
    let temperature = [];
    let humidity = [];
    let heatindex = [];
    temp.forEach((row) => {
      temperature.push({ x: row["_id"], y: row["count"] });
    });
    humid.forEach((row) => {
      humidity.push({ x: row["_id"], y: row["count"] });
    });
    hi.forEach((row) => {
      heatindex.push({ x: row["_id"], y: row["count"] });
    });
    histo.value.series[0].setData(temperature);
    histo.value.series[1].setData(humidity);
    histo.value.series[2].setData(heatindex);
  }
};

const updateScatter = async () => {
  if (!!start.value && !!end.value) {
    // Convert output from Textfield components to 10 digit timestamps
    let startDate = new Date(start.value).getTime() / 1000;
    let endDate = new Date(end.value).getTime() / 1000;
    // Fetch data from backend
    const data = await AppStore.getAllInRange(startDate, endDate);
    // Create arrays for each plot
    let scatterPoints1 = [];
    let scatterPoints2 = [];
    // Iterate through data variable and transform object to format recognized by highcharts
    data.forEach((row) => {
      scatterPoints1.push({
        x: parseFloat(row.temperature.toFixed(2)),
        y: parseFloat(row.heatindex.toFixed(2)),
      });
    });

    data.forEach((row) => {
      scatterPoints2.push({
        x: parseFloat(row.humidity.toFixed(2)),
        y: parseFloat(row.heatindex.toFixed(2)),
      });
    });
    // Add data to Temperature and Heat Index chart
    tempHiScat.value.series[0].setData(scatterPoints1);
    humScat.value.series[0].setData(scatterPoints2);
  }
};

</script>

<style scoped>
/** CSS STYLE HERE */

.container {
  background-color: #f5f5f5;
  width: 1200px;
}

.row {
  max-width: 1200px;
}

.row1 {
  max-width: 1200px;
  padding: 1;
}

.col1 {
  border: black;
}

.sheet {
  padding: 2;
  height: 250;
}

Figure {
  border: 2px solid black;
}
</style> 