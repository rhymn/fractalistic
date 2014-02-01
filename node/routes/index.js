
/*
 * GET home page.
 */

exports.index = function(req, res){
  res.render('index', { title: 'fractalistic' });
};

exports.helloworld = function(req, res){
  res.render('helloworld', { title: 'hello world' });
};


exports.getweatherdata = function(req, res){
  var request = require('request');

  request({
    'url': 'http://opendata-download-metfcst.smhi.se/api/category/pmp1g/version/1/geopoint/lat/57.26/lon/12.41/data.json',
    'json': true

  }, function(error, response, body){

    if(!error && response.statusCode === 200){

      var weatherdata = body.timeseries[0];

      res.send(weatherdata);
    }

  });

};


exports.setdata = function(req, res){
  var request = require('request');
  request({
    // 'url': 'http://r.pnd.se:8192',
    'url': 'http://api.tumblr.com/v2/blog/scipsy.tumblr.com/info?api_key=fuiKNFp9vQFvjLNvx4sUwti4Yb5yGutBN4Xh10LXZhhRKjWlV4',
    'json': true
  }, function(error, response, body){

    if (!error && response.statusCode === 200) {
      res.send(body.response.blog);
    }
    
  });

};

