<?php

DEFINE ('SQL_LOGIN','farawebbase');
DEFINE ('SQL_PWD',  'Bpwpmiy9');
DEFINE ('SQL_DB',   'farawebbase');
DEFINE ('SQL_HOST', 'mysql51-30.perso');

ini_set('display_errors', 1);
ini_set('log_errors', 1);
ini_set('error_log', dirname(__FILE__) . '/error_log.txt');
error_reporting(E_ALL);
if(isset($_GET["score"]) && isset($_GET["name"]) && isset($_GET["checksum"]) ){
	$_POST["score"]=$_GET["score"];
	$_POST["name"]=$_GET["name"];
	$_POST["checksum"]=$_GET["checksum"];
}
if(isset($_GET["str"])){
	$_POST["str"]=$_GET["str"];
}
if(isset($_GET['checkhack'])&&isset($_GET['name'])&&isset($_GET['score']))
	exit("checksum=".encode($_GET['name'],$_GET['score']));
if(isset($_POST["score"]) && isset($_POST["name"]) && isset($_POST["checksum"]) ){
	preg_match('#[a-z]+#',$_POST['checksum'],$tmp);
	$tmp=(isset($tmp[0]))?$tmp[0]:"";
	$_POST['checksum']=$tmp;
	if(preg_match('#^'.encode($_POST["name"],$_POST["score"]).'#',$_POST["checksum"])){
		echo "checksum valid =>";
		$_POST['name']=preg_replace('#[^\w]#', '_',$_POST['name']);
		$_POST['score']=(int) $_POST['score'];
		$sql=mysql_connect(SQL_HOST,SQL_LOGIN,SQL_PWD) or die("Couldn't connect to database, score not saved" );
		mysql_select_db(SQL_DB) or die("Couldn't connect to database, score not saved" );
		$req=mysql_query("SELECT count(*) as nbr FROM   `dk` WHERE  `name` =  '".mysql_real_escape_string(format($_POST["name"]))."' AND  `score` =  '".mysql_real_escape_string($_POST["score"])."';") or die("Couldn't update database, score not saved\n");
		if(mysql_result($req, 0)!=0){
			$query="UPDATE  `dk` SET  `timestamp` = NOW( ) WHERE  `dk`.`name` = '".mysql_real_escape_string(format($_POST["name"]))."' AND `dk`.`score` = '".mysql_real_escape_string($_POST["score"])."';" or die("Couldn't update database, score not saved\n");
			$req=mysql_query($query)or die ("Couldn't update database, score not saved\n");
			echo "Score Updated";
		}else{
		$req=mysql_query("INSERT INTO `dk` (`id` ,`timestamp` ,`name` ,`score`)VALUES (NULL ,CURRENT_TIMESTAMP , '".mysql_real_escape_string(format($_POST["name"]))."', '".mysql_real_escape_string($_POST["score"])."');") or die("Couldn't update database, score not saved" );
		echo "Score Uploaded";
		}
		@mysql_close($sql);
	}else
		echo "Bad checksum";
}else{
	if(!isset($_POST["str"])){
		echo "<h3>Actual score:</h3><br />";
	}
	$sql=mysql_connect(SQL_HOST,SQL_LOGIN,SQL_PWD) or die("Couldn't connect to database" );
	mysql_select_db(SQL_DB) or die("Couldn't connect to database" );
	$req=mysql_query("SELECT * FROM  `dk` ORDER BY  `score` DESC ".((isset($_POST["str"]))?"LIMIT 0 , 12":"")) or die("Couldn't list database..." );
	$i=0;
	while($result=mysql_fetch_array($req)){
		if(isset($_POST["str"]))
			echo format($result['name'])." ".$result['score']."\n";
		else
			echo (++$i)."Joueur: ".format($result['name'])." - ".$result['score']."<br />";
	}
	mysql_close($sql);
}

function encode($a,$b){
    $retour=array();
    //si a est plus long que b on inverse
    if(strlen($b)>strlen($a)){
        $swap=$a;
        $a=$b;
       $b=$swap;
    }
    //on créé le checksum
    for($i=0;$i<strlen($a);$i++){//pour chaque chars du plus grand
       $tmp=chr(((ord($a[$i])+7) ^ (ord($b[$i%strlen($b)])-7))%26+97);//on fait un xor avec quelques chiffres speciaux...
       $retour[$i%20]=$tmp;//on insere dans retour
    }

    return implode($retour);
}

function format($data){
	return preg_replace("#[^a-zA-Z0-9\-_\.*!:?,]#","_",$data);
}

function table_format(){
	$sql=mysql_connect(SQL_HOST,SQL_LOGIN,SQL_PWD) or die("Couldn't connect to database" );
	mysql_select_db(SQL_DB) or die("Couldn't connect to database" );
	$req=mysql_query("SELECT * FROM  `dk`") or die("Couldn't list database..." );
	while($result=mysql_fetch_array($req)){
		echo "update ".$result['name']."<br />";
		$req2=mysql_query("UPDATE `dk` SET `name` = '".mysql_real_escape_string(format($result['name']))."' WHERE `name` = '".mysql_real_escape_string($result['name'])."'") or die("Couldn't update database...<br />".mysql_error() );
	}
	mysql_close($sql);
}


?>
