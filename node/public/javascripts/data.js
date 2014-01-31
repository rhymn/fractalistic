$(function(){
	$('#inc-temp').on('click', function(e){

		$.get( '/setdata', function(data) {
			console.log( data );
		});

	});
});