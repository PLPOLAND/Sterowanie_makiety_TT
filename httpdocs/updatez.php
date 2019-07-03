<?php
  $gr = $_GET['gr'];
  $licz = 0;
    require_once "connection.php";
    $connect = @new mysqli($server, $admin, $pass, $db);
    if ($connect->connect_errno!=0) {
      echo "Error: ".$connect->connect_errno;
    }
    else {
      $connect -> query("SET NAMES 'utf8mb4'");
      if ($rezultat= $connect->query("SELECT * FROM stan WHERE grupa =\"".$gr."\"")) {
        $wierszy = $rezultat->num_rows;
        if($wierszy>0) {
          while ($wiersz = $rezultat->fetch_assoc()) {
            //zwrotnice
                  if ($rezultat= $connect->query("SELECT * FROM stan WHERE grupa =".$gr)) {
                    $wierszy = $rezultat->num_rows;
                    if($wierszy>0) {
                      while ($wiersz = $rezultat->fetch_assoc()) {
                        $command = $wiersz['komenda'];
                        $num = $wiersz['nr'];
                          if ($wiersz['stan']==1) {
                              if ($rezultat1= $connect->query("UPDATE stan  SET stan = 0 WHERE nr =\"".$num."\"")){
                              }
                              else {
                                echo "nie podlaczono";
                              }
                           }
                          else if ($wiersz['stan']==0) {
                            if ($licz==0) {
                              echo $command;
                              $service_url = 'http://192.168.1.3'.$command;
                              $curl = curl_init($service_url);
                              curl_setopt($curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4 );
                              curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
                              $curl_response = curl_exec($curl);
                              curl_close($curl);
                              $licz++;
                            }
                            if ($rezultat2= $connect->query("UPDATE stan  SET stan = 1 WHERE nr =\"".$num."\"")){
                            }
                            else {
                                echo "nie podlaczono";
                            }
                          }
                      }
                    }
                  }
          }
        }
      }
      $connect->close();
    }
?>
