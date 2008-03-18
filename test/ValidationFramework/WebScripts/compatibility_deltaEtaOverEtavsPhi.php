<? include 'compatibility_base.php'; ?>

<html>

<head>
  <title>Compatibility vs eta-ring</title>
  <meta content="Thomas Punz & Ronald Remington" name="author">
  <script type="text/javascript">
		<? generate_javascript("DeltaEtaOverEtavsPhi/DeltaEtaOverEtavsPhiCompare_etBin"); ?>
  </script>
</head>

<body>

<style type="text/css">
	@import url("stylesheet.css");
</style>

<? 

	generate_map("DeltaEtaOverEtavsPhidET_Score_vs_et", "DeltaEtaOverEtavsPhi/DeltaEtaOverEtavsPhiCompare_etBin");
	generate_other_pictures("DeltaEtaOverEtavsPhidPhi_Allbins", "DeltaEtOverEtvsPhiSigmaDeltaEtaOverEta_vs_Phi");
	
?>

</body>
</html>