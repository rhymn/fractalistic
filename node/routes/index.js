
/*
 * GET home page.
 */



exports.index = function(req, res){
  isLocal = false;

  if(req.headers.host.split(':')[0] == 'localhost'){
    isLocal = true;
  }

  res.render('index', { title: 'fractalistic', 'local': isLocal });
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

exports.initdb = function(req, res){
  var pg = require('pg');
  var url = process.env.DATABASE_URL || 'postgres://nodetest:nodetest@localhost:5432/david';

  var date = new Date();

  var client = new pg.Client(url);
  client.connect();
  client.query('DROP TABLE IF EXISTS settings');
  client.query('DROP TABLE IF EXISTS stat');

  client.query('CREATE TABLE settings(id SERIAL, mode VARCHAR, date DATE)');
  client.query('CREATE TABLE stat(id SERIAL, mode VARCHAR, date DATE, t VARCHAR)');

  client.query('INSERT INTO settings(id, date) VALUES(1, $1)', [date]);
  client.query('INSERT INTO stat(id, date) VALUES(1, $1)', [date]);

  res.send(':)');
}

exports.setdata = function(req, res){

  var mode = req.query.mode || null;

  if(mode != 'home' && mode != 'away'){

  }

  var pg = require('pg');
  var url = process.env.DATABASE_URL || 'postgres://nodetest:nodetest@localhost:5432/david';

  var date = new Date();

  var client = new pg.Client(url);
  client.connect();
  client.query('UPDATE settings SET date=$1, mode=$2 WHERE id=1', [date, mode]);

  res.send(':)');
};










