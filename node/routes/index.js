
/*
 * GET home page.
 */

exports.index = function(req, res){
  var isLocal = false;

  if(req.headers.host.split(':')[0] == 'localhost'){
    isLocal = true;
  }

  res.render('index', { title: 'fractalistic', 'local': isLocal });
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
  var pg = require('pg');

  console.log(process.env.DATABASE_URL);

  pg.connect(process.env.DATABASE_URL, function(err, client, done) {
    client.query('INSERT INTO test(name) VALUES("david")');
  });

  res.send('away');
};

