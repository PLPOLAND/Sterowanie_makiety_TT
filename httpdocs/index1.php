<html>
<head>
<meta http-equiv="Content-type" content="text/html; charset=ISO-8859-2" />
<link href="style.css" rel="stylesheet" type="text/css" />
<link href="https://fonts.googleapis.com/css?family=Ubuntu" rel="stylesheet">
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.0/jquery.min.js"></script>
<script src="script.js"></script>
<title>Sterowanie Makietą</title>
</head>
<body>

  <div id="content">
    <div id="semafory">
      <?php
	     // podłączamy bazę php
	      require_once "connection.php";
	       $licz=0;
	        $licznik=0;
          $connect = @new mysqli($server, $admin, $pass, $db);
          if ($connect->connect_errno!=0) {
            echo "Error: ".$connect->connect_errno;
          }
          else {
		          $connect -> query("SET NAMES 'utf8mb4'");
              if ($rezultat= $connect->query("SELECT * FROM stan WHERE co = 0"))
		            {
			               $wierszy = $rezultat->num_rows;
			                  if($wierszy>0) {
				                      while ($wiersz = $rezultat->fetch_assoc()) {
                                if ($wiersz['stan'] == "1") {
                                  echo  "<div class=\"semcz\" id=\"".$wiersz['nr']."\" onclick=\"sem(this.id,".$wiersz['co'].")\">".$wiersz['nr']."</div>";
                                }
                                elseif ($wiersz['stan'] == "0") {
                                  echo  "<div class=\"sem\" id=\"".$wiersz['nr']."\" onclick=\"sem(this.id,".$wiersz['co'].")\">".$wiersz['nr']."</div>";
                                }

    				                  }
    			              }
              }
          }
          $connect->close();
      ?>
      <div style="clear:both;"></div>
    </div>
    <div id="zwrotnice">
        <div id="te"></div>
      <?php
      $licznik = 0;
       // podłączamy bazę php
        require_once "connection.php";
         $licz=0;
          $licznik=0;
          $connect = @new mysqli($server, $admin, $pass, $db);
          if ($connect->connect_errno!=0) {
            echo "Error: ".$connect->connect_errno;
          }
          else {
              $connect -> query("SET NAMES 'utf8mb4'");
              if ($rezultat= $connect->query("SELECT * FROM stan WHERE co = 1"))
                {
                     $wierszy = $rezultat->num_rows;
                        if($wierszy>0) {
                              while ($wiersz = $rezultat->fetch_assoc()) {
                                if ($licznik == 0) {
                                  echo "<div class=\"contener\">";
                                }
                                if ($wiersz['stan'] == "0") {
                                  echo  "<div class=\"zw ".$wiersz['grupa']."\" id=\"".$wiersz['nr']."\" onclick=\"zwrot(this.id,".$wiersz['co'].",".$wiersz['grupa'].",'".$wiersz['komenda']."')\">".$wiersz['nr']."</div>";
                                }
                                elseif ($wiersz['stan'] == "1") {
                                  echo  "<div class=\"zwz ".$wiersz['grupa']."\" id=\"".$wiersz['nr']."\" onclick=\"zwrot(this.id,".$wiersz['co'].",".$wiersz['grupa'].",'".$wiersz['komenda']."')\">".$wiersz['nr']."</div>";
                                }
                                if ($licznik == 0) {
                                  $licznik++;
                                }
                                else if ($licznik == 1){
                                  echo "<div style=\"clear:both;\"></div></div>";
                                  $licznik=0;
                                }
                              }
                        }
              }
          }
          $connect->close();
      ?>
    </div>
  <div id="reset" onclick="reset()">R</div>

  </div>
</body>
</html>
