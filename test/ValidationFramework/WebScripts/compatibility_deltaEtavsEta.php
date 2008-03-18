<? include 'compatibility_base.php'; ?>

<html>

<head>
  <title>Compatibility vs eta-ring</title>
  <meta content="Thomas Punz & Ronald Remington" name="author">
  <script type="text/javascript">
		<? generate_javascript("DeltaEtavsEta/DeltaEtavsEtaCompare_etBin"); ?>
  </script>
</head>

<body>

<style type="text/css">
	@import url("stylesheet.css");
</style>

<? 

	generate_map("DeltaEtavsEtadET_Score_vs_et", "DeltaEtavsEta/DeltaEtavsEtaCompare_etBin");
	generate_other_pictures("DeltaEtavsEtadEta_Allbins", "DeltaEtavsEtaSigmaDeltaEta_vs_Eta");
	
?>

</body>
</html>