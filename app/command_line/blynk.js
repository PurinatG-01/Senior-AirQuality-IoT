const fetch = require("node-fetch");

let result = {};
const auth_token = "GS3mZFpy8AJTO97oFDyxUd8d_sujg_d_";


console.log("--------------------- Air Quality Sensors ---------------------");
let loop_count = 0;
setInterval(() => {
  
  const getData = async ()=>{
    try{
      console.log(`---------------------- ${loop_count++} ---------------------- `);
      let res0 = await fetch(`http://blynk-cloud.com/${auth_token}/get/v0`);
      let v0 = await res0.json();
      
      let res1 = await fetch(`http://blynk-cloud.com/${auth_token}/get/v1`);
      let v1 = await res1.json();
      let res2 = await fetch(`http://blynk-cloud.com/${auth_token}/get/v2`);
      let v2 = await res2.json();
      let res3 = await fetch(`http://blynk-cloud.com/${auth_token}/get/v3`);
      let v3 = await res3.json();
      let res4 = await fetch(`http://blynk-cloud.com/${auth_token}/get/v4`);
      let v4 = await res4.json();  

      let res5 = await fetch(`http://blynk-cloud.com/${auth_token}/get/v5`);
      let v5 = await res5.json();
      let res6 = await fetch(`http://blynk-cloud.com/${auth_token}/get/v6`);
      let v6 = await res6.json();
      let res7 = await fetch(`http://blynk-cloud.com/${auth_token}/get/v7`);
      let v7 = await res7.json();

      console.log(`CO2          : ${v0[0]} ppm`);


      console.log(`Temperature  : ${v1[0]} C`);
      console.log(`Humidity     : ${v2[0]} %`);
      console.log(`Pressure     : ${v3[0]} Pa`);
      console.log(`Gas          : ${v4[0]} mOhm`);

      console.log(`PM 1.0        : ${v5[0]} ppm`);
      console.log(`PM 2.5        : ${v6[0]} ppm`);
      console.log(`PM 10.0       : ${v7[0]} ppm`);
    }catch(error){
      console.error(`> error : ${error}`);
    }
    

  };
  getData();
}, 2000);
