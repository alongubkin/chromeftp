$(function() {
	var hosts = localStorage.getObject('hosts');
	
	if (hosts === null) {
		hosts = [];
		localStorage.setObject('hosts', []);
	}
	
	if (hosts !== null) {
		for (var counter = 0; counter < hosts.length; counter++) {
			var host = hosts[counter];
			
			$('#hosts-select').append(
				$('<option></option>')
					.text(host.name)
					.val(counter)
			);
		}
	}
	
	$('#hosts-examplebutton').click(function() {
		hosts.push({
			
		});
	});
});