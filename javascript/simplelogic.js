// simplelogic.js
YUI().use("node","app-base", function(Y){

	Y.log("YUI is ready");

	var app = new Y.App({
		// app config here soon
	});

	// handle request for root

	app.route('/',function(){
		Y.one('h1').set('text', 'SimpleApp - home state');
	});

	// handle all other requests right now.

	app.route('*', function(req){
		Y.one('h1').set('text', 'SimpleApp - ' + req.path + ' - state');
	});

	app.render().dispatch();

});