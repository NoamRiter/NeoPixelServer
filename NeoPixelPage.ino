void NeoPixelPage(){
  javascriptNeoPixelPage();
  getHeader();
     webpage += "<div class=\"container\">\n";
      webpage += "<div>\n";
      webpage += "<button type=\"button\" class=\"btn btn-default\" onClick=\"sendColor(0)\">off</button>\n";
      webpage += "</div>\n";

      webpage += "<br/>\n";

      webpage += "<div>\n";
      webpage += "<button type=\"button\" class=\"btn btn-danger\" onClick=\"sendColor(1)\">Red</button>\n";
      webpage += "<button type=\"button\" class=\"btn btn-success\" onClick=\"sendColor(2)\">Green</button>\n";
      webpage += "<button type=\"button\" class=\"btn btn-primary\" onClick=\"sendColor(3)\">Blue</button>\n";
      webpage += "</div>\n";

      webpage += "<br/>\n";

      webpage += "<div>\n";
      webpage += "<button type=\"button\" class=\"btn btn-default\" onClick=\"sendColor(4)\">theaterChase White</button>\n";
      webpage += "<button type=\"button\" class=\"btn btn-danger\" onClick=\"sendColor(5)\">theaterChase Red</button>\n";
      webpage += "<button type=\"button\" class=\"btn btn-primary\" onClick=\"sendColor(6)\">theaterChase Blue</button>\n";
      webpage += "</div>\n";

      webpage += "<br/>\n";

      webpage += "<div>\n";
      webpage += "<button type=\"button\" class=\"btn btn-link\" onClick=\"sendColor(7)\">rainbow</button>\n";
      webpage += "<button type=\"button\" class=\"btn btn-link\" onClick=\"sendColor(8)\">rainbow Cycle</button>\n";
      webpage += "<button type=\"button\" class=\"btn btn-link\" onClick=\"sendColor(9)\">theaterChase Rainbow</button>\n";
      webpage += "</div>\n";

     webpage += "</div>\n";


      
     
       
  getFooter();
  server.send(200, "text/html", webpage);
}

void javascriptNeoPixelPage(){  // here you can add javascript to this page
  javaScript = "<script type=\"text/javascript\">\n";
  javaScript += "function sendColor(Value){\n";
  javaScript += "req = new XMLHttpRequest();\n";
  javaScript += "url =\"http://" + IpAddress + "/startShow\";\n";
  javaScript += "var data = {value: Value};\n";
  javaScript += "req.open(\"POST\", url);\n";
  javaScript += "req.send(JSON.stringify(data));\n";
  javaScript += "}\n";
  javaScript += "</script>\n";
}
