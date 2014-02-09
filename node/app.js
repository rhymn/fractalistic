
/**
 * Module dependencies.
 */

var express = require('express');
var routes = require('./routes');
var user = require('./routes/user');
var http = require('http');
var path = require('path');

var app = express();

// all environments
app.set('port', process.env.PORT || 3000);
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'jade');
app.use(express.logger('dev'));
app.use(express.json());
app.use(express.urlencoded());
app.use(express.methodOverride());
app.use(app.router);
app.use(express.static(path.join(__dirname, 'public')));

// development only
if ('development' == app.get('env')) {
  app.use(express.errorHandler());
}

app.get('/', routes.index);
app.get('/users', user.list);

app.get('/setsettings', routes.setsettings);
app.get('/getsettings', routes.getsettings);

app.get('/setstat/temp/:temp/mode/:mode', routes.setstat);
app.get('/getstat', routes.getstat);

app.get('/getweatherdata', routes.getweatherdata);

http.createServer(app).listen(app.get('port'), function(){
  console.log('fractalistic listening on port ' + app.get('port'));
});
