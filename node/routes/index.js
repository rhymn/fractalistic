

var mongo = require('mongodb');
var url = process.env.MONGOHQ_URL || 'mongodb://fractalistic:fractalistic-pwd@troup.mongohq.com:10080/fractalistic';



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

exports.getsettings = function(req, res){
  mongo.Db.connect(url, function (err, db) {
    db.collection('settings', function(er, collection) {
      collection.findOne({key:1}, function(er, item) {
        res.json(item);
      });
    });
  });
}

exports.setsettings = function(req, res){

  var mode = req.query.mode || null;

  if(mode != 'home' && mode != 'away'){
    res.send(':(');
    return;
  }

  var date = new Date();

  mongo.Db.connect(url, function (err, db) {
    db.collection('settings', function(er, collection) {
      collection.update({key:1}, {$set:{'mode': mode, 'date': date}}, {safe: true}, function(er,rs) {
      });
    });
  });

  res.send(':)');
};





exports.getstat = function(req, res){
  mongo.Db.connect(url, function (err, db) {
    db.collection('stat', function(er, collection) {
      collection.findOne({key:1}, function(er, item) {
        res.json(item);
      });
    });
  });
}

exports.setstat = function(req, res){
  var date = new Date();

  var temp = req.params.temp;

  var mode = 'home';

  mongo.Db.connect(url, function (err, db) {
    db.collection('settings', function(er, collection) {
      collection.update({key:1}, {$set:{'mode': mode, 'date': date, 'temp': temp}}, {safe: true}, function(er,rs) {
      });
    });
  });

  res.send(':)');
};



