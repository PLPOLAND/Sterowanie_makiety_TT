function sem(id,what) {
		$.get( "update.php", {
			komenda: id, co: what} );
    colory(id);
}
function zwrot(grupa) {
		$.get( "updatez.php", {
			gr: grupa } );
			color(grupa);
}

function colory(id) {
  var ida = "#"+id;
  var color = $(ida).css("background-color");

  if (color == "rgb(255, 0, 0)") {
    $(ida).css("background-color", "rgb(57, 218, 0)");
  }
  else {
    $(ida).css("background-color", "rgb(255, 0, 0)");
  }
}


function color(grupa) {
  var ida = document.getElementsByClassName(grupa);
  var colorOne = $(ida.item(0)).css("background-color");
	var colorTwo = $(ida.item(1)).css("background-color");
	if (colorOne == "rgb(128, 128, 128)") {
		$(ida.item(1)).addClass("zw");
		$(ida.item(1)).removeClass("zwz");
		$(ida.item(0)).addClass("zwz");
		$(ida.item(0)).removeClass("zw");
  }
  else {
		$(ida.item(0)).addClass("zw");
		$(ida.item(0)).removeClass("zwz");
		$(ida.item(1)).addClass("zwz");
		$(ida.item(1)).removeClass("zw");
  }
}


function reset() {
	setTimeout(function () {odswierz();}, 3000);
  $.get( "update.php", {
  komenda: "/reset"} );
}
function odswierz() {
	location.reload();
}
