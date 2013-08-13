<?

require_once('lib.php');
$limit = $_GET['limit'];

?>


<!DOCTYPE html>
<html>
	<head>
		<title>fractalistic</title>
		<meta name="viewport" content="width=device-width, initial-scale=1.0">
		<meta charset="UTF-8" />
		<link href="bootstrap/css/bootstrap.min.css" rel="stylesheet" media="screen">
		<link href="bootstrap/css/bootstrap-responsive.min.css" rel="stylesheet" media="screen">
		<link href="css/arduino.css" rel="stylesheet" media="screen">
	</head>

	<body>
		<!-- Part 1: Wrap all page content here -->
		<div id="wrap">

			<!-- Begin page content -->
			<div class="container">
				<div class="page-header">
					<h1>fractalistic</h1>

					<form id="form">
						Visa <input name="limit" id="limit" value="<?=$limit?>" maxlength="5" style="width: 50px;" /> rader
					</form>
				</div>
				
				<table class="table">
					<th>
						<td>Tid</td>
						<td>Output</td>
						<td>Ref</td>
						<td>R</td>
						<td>T</td>
						<td>lastInput</td>
						<td>lastError</td>
						<td>lastOutput</td>
						<td>P</td>
						<td>I</td>
						<td>D</td>
					</th>
					
					<?
						$datasets = array(
							'output' => array(
								'label' => 'Output',
								'data' => array()
							),
							'ref' => array(
								'label' => 'Ref',
								'data' => array()
							),
							/*'R' => array(
								'label' => 'Res',
								'data' => array()
							),*/
							'T' => array(
								'label' => 'Temp',
								'data' => array()
							),
							'lastInput' => array(
								'label' => 'Senaste in',
								'data' => array()
							),
							'lastError' => array(
								'label' => 'Senaste fel',
								'data' => array()
							),
							'lastOutput' => array(
								'label' => 'Senaste ut',
								'data' => array()
							),
							'p' => array(
								'label' => 'P',
								'data' => array()
							),
							'i' => array(
								'label' => 'I',
								'data' => array()
							),
							'd' => array(
								'label' => 'D',
								'data' => array()
							)
						);
					
					$result = readFromDB($limit);

					foreach($result as $row):
					
						$time = (int) ($row['time'] / 1000);
						
						$output[] 							= array($time, (float) $row['output']);
						$datasets['output']['data'][] 		= array($time, (float) $row['output']);

						$ref[] 								= array($time, (float) $row['ref']);
						$datasets['ref']['data'][] 			= array($time, (float) $row['ref']);

						$R[] 								= array($time, (float) $row['R']);
						// $datasets['R']['data'][] 			= array($time, (float) $row['R']);

						$T[] 								= array($time, (float) $row['T']);
						$datasets['T']['data'][] 			= array($time, (float) $row['T']);

						$lastInput[] 						= array($time, (float) $row['lastInput']);
						$datasets['lastInput']['data'][]	= array($time, (float) $row['lastInput']);

						$lastError[] 						= array($time, (float) $row['lastError']);
						$datasets['lastError']['data'][] 	= array($time, (float) $row['lastError']);

						$lastOutput[] 						= array($time, (float) $row['lastOutput']);
						$datasets['lastOutput']['data'][] 	= array($time, (float) $row['lastOutput']);

						$p[] 								= array($time, (float) $row['p']);
						$datasets['p']['data'][] 			= array($time, (float) $row['p']);

						$i[] 								= array($time, (float) $row['i']);
						$datasets['i']['data'][] 			= array($time, (float) $row['i']);

						$d[] 								= array($time, (float) $row['d']);
						$datasets['d']['data'][] 			= array($time, (float) $row['d']);
	
					?>
						<tr>
							<td><?=$row['date'] ?></td>
							<td><?=$row['time'] ?></td>
							<td><?=$row['output'] ?></td>
							<td><?=$row['ref'] ?></td>
							<td><?=$row['R'] ?></td>
							<td><?=$row['T'] ?></td>
							<td><?=$row['lastInput'] ?></td>
							<td><?=$row['lastError'] ?></td>
							<td><?=$row['lastOutput'] ?></td>
							<td><?=$row['p'] ?></td>
							<td><?=$row['i'] ?></td>
							<td><?=$row['d'] ?></td>
						</tr>
					<? endforeach; ?>
					
				</table>


			</div>
			
			<div class="demo-container">
				<div id="placeholder" class="demo-placeholder"></div>
			</div>
			

			<div id="push"></div>
		</div>

		<div id="footer">
			<div class="container">
				<p class="muted credit">fractalistic</p>
			</div>
		</div>


		<!--- <script src="//ajax.googleapis.com/ajax/libs/jquery/1.9.1/jquery.min.js"></script> --->
		<script>window.jQuery || document.write('<script src="js/jquery-1.9.1.min.js"><\/script>')</script>
		<script src="bootstrap/js/bootstrap.js"></script>
		<script src="../flot/jquery.flot.js"></script>
		
		<!-- HTML5 shim, for IE6-8 support of HTML5 elements -->
		<!--[if lt IE 9]>
			<script src="js/html5shiv.js"></script>
		<![endif]-->

		<script>

			jQuery(function(){
				jQuery('#limit').keyup(function(e){
					if(e.keyCode == 13){
						jQuery('#form').submit();
					}
				});
			});

			var datasets = eval(<?=json_encode($datasets) ?>);
			
			var datasetArray = [];
			
			$.each(datasets, function(key, val){
				datasetArray.push(val);
			});
		
			$.plot("#placeholder", datasetArray);
		</script>

	</body>
</html>
