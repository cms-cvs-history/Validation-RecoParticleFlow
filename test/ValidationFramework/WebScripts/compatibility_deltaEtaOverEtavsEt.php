<? include 'compatibility_base.php'; ?>

<html>

<head>
  <title>Compatibility vs eta-ring</title>
  <meta content="Thomas Punz & Ronald Remington" name="author">
  <script type="text/javascript">
		<? generate_javascript("DeltaEtaOverEtavsEt/DeltaEtaOverEtavsEtCompare_etBin"); ?>
  </script>
</head>

<body>

<style type="text/css">
	@import url("stylesheet.css");
</style>

<? 

	generate_map("DeltaEtaOverEtavsEtdET_Score_vs_et", "DeltaEtaOverEtavsEt/DeltaEtaOverEtavsEtCompare_etBin");
	generate_other_pictures("DeltaEtaOverEtavsEtdEt_Allbins", "DeltaEtaOverEtavsEtSigmaDeltaEtaOverEta_vs_Et");
	
?>

</body>
</html>