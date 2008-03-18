<? include 'compatibility_base.php'; ?>

<html>

<head>
  <title>Compatibility vs eta-ring</title>
  <meta content="Thomas Punz & Ronald Remington" name="author">
  <script type="text/javascript">
		<? generate_javascript("DeltaEtavsPhi/DeltaEtavsPhiCompare_etBin"); ?>
  </script>
</head>

<body>

<style type="text/css">
	@import url("stylesheet.css");
</style>

<? 

	generate_map("DeltaEtavsPhidET_Score_vs_et", "DeltaEtavsPhi/DeltaEtavsPhiCompare_etBin");
	generate_other_pictures("DeltaEtavsPhidPhi_Allbins", "DeltaEtavsPhiSigmaDeltaEta_vs_Phi");
	
?>

</body>
</html>