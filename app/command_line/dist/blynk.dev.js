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
            _context.next = 3;
            return regeneratorRuntime.awrap(fetch("http://blynk-cloud.com/".concat(auth_token, "/get/v0")));

          case 3:
            res0 = _context.sent;
            _context.next = 6;
            return regeneratorRuntime.awrap(res0.json());

          case 6:
            v0 = _context.sent;
            _context.next = 9;
            return regeneratorRuntime.awrap(fetch("http://blynk-cloud.com/".concat(auth_token, "/get/v1")));

          case 9:
            res1 = _context.sent;
            _context.next = 12;
            return regeneratorRuntime.awrap(res1.json());

          case 12:
            v1 = _context.sent;
            _context.next = 15;
            return regeneratorRuntime.awrap(fetch("http://blynk-cloud.com/".concat(auth_token, "/get/v2")));

          case 15:
            res2 = _context.sent;
            _context.next = 18;
            return regeneratorRuntime.awrap(res2.json());

          case 18:
            v2 = _context.sent;
            _context.next = 21;
            return regeneratorRuntime.awrap(fetch("http://blynk-cloud.com/".concat(auth_token, "/get/v3")));

          case 21:
            res3 = _context.sent;
            _context.next = 24;
            return regeneratorRuntime.awrap(res3.json());

          case 24:
            v3 = _context.sent;
            _context.next = 27;
            return regeneratorRuntime.awrap(fetch("http://blynk-cloud.com/".concat(auth_token, "/get/v4")));

          case 27:
            res4 = _context.sent;
            _context.next = 30;
            return regeneratorRuntime.awrap(res4.json());

          case 30:
            v4 = _context.sent;
            _context.next = 33;
            return regeneratorRuntime.awrap(fetch("http://blynk-cloud.com/".concat(auth_token, "/get/v5")));

          case 33:
            res5 = _context.sent;
            _context.next = 36;
            return regeneratorRuntime.awrap(res5.json());

          case 36:
            v5 = _context.sent;
            _context.next = 39;
            return regeneratorRuntime.awrap(fetch("http://blynk-cloud.com/".concat(auth_token, "/get/v6")));

          case 39:
            res6 = _context.sent;
            _context.next = 42;
            return regeneratorRuntime.awrap(res6.json());

          case 42:
            v6 = _context.sent;
            _context.next = 45;
            return regeneratorRuntime.awrap(fetch("http://blynk-cloud.com/".concat(auth_token, "/get/v7")));

          case 45:
            res7 = _context.sent;
            _context.next = 48;
            return regeneratorRuntime.awrap(res7.json());

          case 48:
            v7 = _context.sent;
            console.log("---------------------- ".concat(loop_count++, " ---------------------- "));
            console.log("CO2          : ".concat(v0[0], " ppm"));
            console.log("Temperature  : ".concat(v1[0], " C"));
            console.log("Humidity     : ".concat(v2[0], " %"));
            console.log("Pressure     : ".concat(v3[0], " Pa"));
            console.log("Gas          : ".concat(v4[0], " mOhm"));
            console.log("PM 1.0        : ".concat(v5[0], " ug/m3"));
            console.log("PM 2.5        : ".concat(v6[0], " ug/m3"));
            console.log("PM 10.0       : ".concat(v7[0], " ug/m3"));
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