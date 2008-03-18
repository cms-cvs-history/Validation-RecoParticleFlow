<? include 'compatibility_base.php'; ?>

<html>

<head>
  <title>Compatibility vs eta-ring</title>
  <meta content="Thomas Punz & Ronald Remington" name="author">
  <script type="text/javascript">
		<? generate_javascript("DeltaEtavsEt/DeltaEtavsEtCompare_etBin"); ?>
  </script>
</head>

<body>

<style type="text/css">
	@import url("stylesheet.css");
</style>

<? 

	generate_map("DeltaEtavsEtdET_Score_vs_et", "DeltaEtavsEt/DeltaEtavsEtCompare_etBin");
	generate_other_pictures("DeltaEtavsEtdEt_Allbins", "DeltaEtavsEtSigmaDeltaEta_vs_Et");
	
?>

</body>
</html>