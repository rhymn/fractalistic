var pg = require('pg');
var url = process.env.DATABASE_URL || 'postgres://nodetest:nodetest@localhost:5432/david';

var client = new pg.Client(url);

client.connect();

var query = client.query('CREATE TABLE settings (date date)');

query.on('end', function(){ client.end(); });
