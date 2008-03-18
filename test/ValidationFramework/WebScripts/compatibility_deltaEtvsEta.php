<? include 'compatibility_base.php'; ?>

<html>

<head>
  <title>Compatibility vs eta-ring</title>
  <meta content="Thomas Punz & Ronald Remington" name="author">
  <script type="text/javascript">
		<? generate_javascript("DeltaEtvsEta/DeltaEtvsEtaCompare_etBin"); ?>
  </script>
</head>

<body>

<style type="text/css">
	@import url("stylesheet.css");
</style>

<? 

	generate_map("DeltaEtvsEtadET_Score_vs_et", "DeltaEtvsEta/DeltaEtvsEtaCompare_etBin");
	generate_other_pictures("DeltaEtvsEtadEta_Allbins", "DeltaEtvsEtaSigmaDeltaEt_vs_Eta");
	
?>

</body>
</html>