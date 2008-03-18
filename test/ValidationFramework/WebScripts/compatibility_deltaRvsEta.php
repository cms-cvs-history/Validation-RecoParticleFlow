<? include 'compatibility_base.php'; ?>

<html>

<head>
  <title>Compatibility vs eta-ring</title>
  <meta content="Thomas Punz & Ronald Remington" name="author">
  <script type="text/javascript">
		<? generate_javascript("DeltaRvsEta/DeltaRvsEtaCompare_etBin"); ?>
  </script>
</head>

<body>

<style type="text/css">
	@import url("stylesheet.css");
</style>

<? 

	generate_map("DeltaRvsEtadET_Score_vs_et", "DeltaRvsEta/DeltaRvsEtaCompare_etBin");
	generate_other_pictures("DeltaRvsEtadEta_Allbins", "DeltaRvsEtaSigmaDeltaR_vs_Eta");
	
?>

</body>
</html>