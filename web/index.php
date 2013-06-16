<?

require_once('lib.php');

?>


<!DOCTYPE html>
<html>
	<head>
		<title>RPi</title>
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
					<h1>Hej</h1>
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
					
					<? foreach($result as $row):
					
						$time = (int) ($row['time'] / 1000);

						$output[] 		= array($time, (float) $row['output']);
						$ref[] 			= array($time, (float) $row['ref']);
						$R[] 			= array($time, (float) $row['R']);
						$T[] 			= array($time, (float) $row['T']);
						$lastInput[] 	= array($time, (float) $row['lastInput']);
						$lastError[] 	= array($time, (float) $row['lastError']);
						$lastOutput[] 	= array($time, (float) $row['lastOutput']);
						$p[] 			= array($time, (float) $row['p']);
						$i[] 			= array($time, (float) $row['i']);
						$d[] 			= array($time, (float) $row['d']);
	
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
				<p class="muted credit">Den store elpanneprojekt</p>
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
			
			var output 			= eval('<?=json_encode($output) ?>');
			var ref 			= eval('<?=json_encode($ref) ?>');
			var R 				= eval('<?=json_encode($R) ?>');
			var T 				= eval('<?=json_encode($T) ?>');
			var lastInput 		= eval('<?=json_encode($lastInput) ?>');
			var lastError		= eval('<?=json_encode($lastError) ?>');
			var lastOutput		= eval('<?=json_encode($lastOutput) ?>');
			var p 				= eval('<?=json_encode($p) ?>');
			var i 				= eval('<?=json_encode($i) ?>');
			var d 				= eval('<?=json_encode($d) ?>');
		
			$.plot("#placeholder", [ output, ref, R, T, lastInput, lastError, lastOutput, p, i, d ]);
		</script>

	</body>
</html>
