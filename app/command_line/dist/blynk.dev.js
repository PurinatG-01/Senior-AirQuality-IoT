"use strict";

var fetch = require("node-fetch");

var result = {};
var auth_token = "GS3mZFpy8AJTO97oFDyxUd8d_sujg_d_";
console.log("--------------------- Air Quality Sensors ---------------------");
var loop_count = 0;
setInterval(function () {
  var getData = function getData() {
    var res0, v0, res1, v1, res2, v2, res3, v3, res4, v4, res5, v5, res6, v6, res7, v7;
    return regeneratorRuntime.async(function getData$(_context) {
      while (1) {
        switch (_context.prev = _context.next) {
          case 0:
            _context.prev = 0;
            console.log("---------------------- ".concat(loop_count++, " ---------------------- "));
            _context.next = 4;
            return regeneratorRuntime.awrap(fetch("http://blynk-cloud.com/".concat(auth_token, "/get/v0")));

          case 4:
            res0 = _context.sent;
            _context.next = 7;
            return regeneratorRuntime.awrap(res0.json());

          case 7:
            v0 = _context.sent;
            _context.next = 10;
            return regeneratorRuntime.awrap(fetch("http://blynk-cloud.com/".concat(auth_token, "/get/v1")));

          case 10:
            res1 = _context.sent;
            _context.next = 13;
            return regeneratorRuntime.awrap(res1.json());

          case 13:
            v1 = _context.sent;
            _context.next = 16;
            return regeneratorRuntime.awrap(fetch("http://blynk-cloud.com/".concat(auth_token, "/get/v2")));

          case 16:
            res2 = _context.sent;
            _context.next = 19;
            return regeneratorRuntime.awrap(res2.json());

          case 19:
            v2 = _context.sent;
            _context.next = 22;
            return regeneratorRuntime.awrap(fetch("http://blynk-cloud.com/".concat(auth_token, "/get/v3")));

          case 22:
            res3 = _context.sent;
            _context.next = 25;
            return regeneratorRuntime.awrap(res3.json());

          case 25:
            v3 = _context.sent;
            _context.next = 28;
            return regeneratorRuntime.awrap(fetch("http://blynk-cloud.com/".concat(auth_token, "/get/v4")));

          case 28:
            res4 = _context.sent;
            _context.next = 31;
            return regeneratorRuntime.awrap(res4.json());

          case 31:
            v4 = _context.sent;
            _context.next = 34;
            return regeneratorRuntime.awrap(fetch("http://blynk-cloud.com/".concat(auth_token, "/get/v5")));

          case 34:
            res5 = _context.sent;
            _context.next = 37;
            return regeneratorRuntime.awrap(res5.json());

          case 37:
            v5 = _context.sent;
            _context.next = 40;
            return regeneratorRuntime.awrap(fetch("http://blynk-cloud.com/".concat(auth_token, "/get/v6")));

          case 40:
            res6 = _context.sent;
            _context.next = 43;
            return regeneratorRuntime.awrap(res6.json());

          case 43:
            v6 = _context.sent;
            _context.next = 46;
            return regeneratorRuntime.awrap(fetch("http://blynk-cloud.com/".concat(auth_token, "/get/v7")));

          case 46:
            res7 = _context.sent;
            _context.next = 49;
            return regeneratorRuntime.awrap(res7.json());

          case 49:
            v7 = _context.sent;
            console.log("CO2          : ".concat(v0[0], " ppm"));
            console.log("Temperature  : ".concat(v1[0], " C"));
            console.log("Humidity     : ".concat(v2[0], " %"));
            console.log("Pressure     : ".concat(v3[0], " Pa"));
            console.log("Gas          : ".concat(v4[0], " mOhm"));
            console.log("PM 1.0        : ".concat(v5[0], " ppm"));
            console.log("PM 2.5        : ".concat(v6[0], " ppm"));
            console.log("PM 10.0       : ".concat(v7[0], " ppm"));
            _context.next = 63;
            break;

          case 60:
            _context.prev = 60;
            _context.t0 = _context["catch"](0);
            console.error("> error : ".concat(_context.t0));

          case 63:
          case "end":
            return _context.stop();
        }
      }
    }, null, null, [[0, 60]]);
  };

  getData();
}, 2000);