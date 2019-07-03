<?php
  $nr = $_GET['komenda'];
  $co = $_GET['co'];
  $gr = $_GET['gr'];
  $kom = $_GET['kome'];
  $licz = 0;
  if ($nr == "/reset") {
    require_once "connection.php";
    $connect = @new mysqli($server, $admin, $pass, $db);
    if ($connect->connect_errno!=0) {
      echo "Error: ".$connect->connect_errno;
    }
    else {
      $connect -> query("SET NAMES 'utf8mb4'");
      if ($rezultat= $connect->query("UPDATE stan  SET stan = 1 ")){
        if ($rezultat= $connect->query("UPDATE stan  SET stan = 0 WHERE nr = \"zB\"")){
        }
        if ($rezultat= $connect->query("UPDATE stan  SET stan = 0 WHERE nr = \"zK\"")){
        }
        if ($rezultat= $connect->query("UPDATE stan  SET stan = 0 WHERE nr = \"z2\"")){
        }
        if ($rezultat= $connect->query("UPDATE stan  SET stan = 0 WHERE nr = \"zCZ\"")){
        }
        $service_url = 'http://192.168.0.3/reset';
        $curl = curl_init($service_url);
        curl_setopt($curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4 );
        curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
        $curl_response = curl_exec($curl);
        curl_close($curl);
      }

    }
  }
else {
  if ($co==0) {

    require_once "connection.php";
    $connect = @new mysqli($server, $admin, $pass, $db);
    if ($connect->connect_errno!=0) {
      echo "Error: ".$connect->connect_errno;
    }
    else {
      $connect -> query("SET NAMES 'utf8mb4'");
      if ($rezultat= $connect->query("SELECT * FROM stan WHERE nr =\"".$nr."\"")) {
        $wierszy = $rezultat->num_rows;
        if($wierszy>0) {
          while ($wiersz = $rezultat->fetch_assoc()) {
            if ($wiersz["stan"]==1) {
              $rezultat1= $connect->query("UPDATE stan  SET stan = 0 WHERE nr =".$nr );
                $service_url = 'http://192.168.0.3/'.$nr.'/0';
                $curl = curl_init($service_url);
                curl_setopt($curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4 );
                curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
                $curl_response = curl_exec($curl);
                curl_close($curl);
            }
            else if ($wiersz["stan"]==0) {
              $rezultat1= $connect->query("UPDATE stan  SET stan = 1 WHERE nr =".$nr );
                $service_url = 'http://192.168.0.3/'.$nr.'/1';
                $curl = curl_init($service_url);
                curl_setopt($curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4 );
                curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
                $curl_response = curl_exec($curl);
                curl_close($curl);
            }
          }
        }
      }
    }
    $connect->close();
  }

  //zwrotnice
  elseif ($co == 1) {
    require_once "connection.php";
    $connect = new mysqli($server, $admin, $pass, $db);
    if ($connect->connect_errno!=0) {
      echo "Error: ".$connect->connect_errno;
    }
    else {
      $connect -> query("SET NAMES 'utf8mb4'");
      /////////////////////////////////////////////////////////////////////////
      if ($rezultat= $connect->query("SELECT * FROM stan WHERE nr =\"".$nr."\"")) {
        $wierszy = $rezultat->num_rows;
        if($wierszy==1) {
          while ($wiersz = $rezultat->fetch_assoc()) {
            $command = $wiersz['komenda'];
          }
        }
      }
          echo $command;
        $service_url = 'http://192.168.0.3'.$command;
        $curl = curl_init($service_url);
        curl_setopt($curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4 );
        curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
        $curl_response = curl_exec($curl);
        curl_close($curl);

    //////////////////////////////////////////////////////////////////////////////

      if ($rezultat= $connect->query("SELECT * FROM stan WHERE grupa =".$gr)) {
        $wierszy = $rezultat->num_rows;
        if($wierszy>0) {
          while ($wiersz = $rezultat->fetch_assoc()) {
            $num = $wiersz['nr'];
              if ($wiersz['stan']==1) {
                  if ($rezultat1= $connect->query("UPDATE stan  SET stan = 0 WHERE nr =\"".$num."\"")){
                    $command = $wiersz['komenda'];
                  }
                  else {
                    echo "nie podlaczono";
                  }
               }
              else if ($wiersz['stan']==0) {
                  if ($rezultat2= $connect->query("UPDATE stan  SET stan = 1 WHERE nr =\"".$num."\"")){
                    $command = $wiersz['komenda'];
                  }
                  else {
                    echo "nie podlaczono";
                  }
              }
          }
        }
      }
    }
    $connect->close();
  }
}
 ?>
