yui3-heroku-example-simple
==========================

Simple example of a YUI3 app deployable to Heroku with steps to use


STEPS TO USE
============
 * Get [Heroku tools](https://devcenter.heroku.com/articles/quickstart) set up
 * Get Github acct set up
 * Install [node](http://nodejs.org/) (you need at least v0.8.x)
 * Fork this project - get your new fork repo url.
 * Clone your new fork locally in your machine. For example: `git clone git@github.com:triptych/yui3-heroku-example-simple.git`
 * Go into created project directory
 * Test locally by running `node server.js`
 * Visit in browser `localhost:3000` - should see a grey page with links
 * Create project from Heroku `heroku create`
 * Check that you now have a heroku remote in your repo `git remote -v`
 * Push code to Heroku `git push heroku master`
 * Try out the site via the heroku link - click the links to see the app update

EDITING
=======
  * Edit files locally
  * Commit files to your github repo `git commit -m "foo"`
  * Push files to your github repo `git push origin master`

DEPLOYING
=========
 * push to Heroku `git push heroku master`


FILES
=====
 * `package.json` - tells node the app name, dependencies, and what version of engines to use.
 * `Procfile` - special file for Heroku to know how to "run" your app once it's up on the server.
 * `server.js` - requires express, sends back simple.html, sets up the redirect so the client side Y.App can handle requests.
 * `simple.html` - basic HTML to serve back - includes Y.App on client side to deal with application logic, pulls in css and logic js.
 * `css/simple.css` - location referenced from `simple.js`, used in `simple.html`
 * `javascript/simplelogic.js` - location referenced from `simple.js`, used in `simple.html`, core logic for your app.


REFERENCES
==========
 * [Deploying with Git](https://devcenter.heroku.com/articles/git)
 * [Github Help](https://help.github.com/)
 * [YUI3 App Framework](http://yuilibrary.com/yui/docs/app/)

Questions? email [triptych@gmail.com](mailto:triptych@gmail.com)
