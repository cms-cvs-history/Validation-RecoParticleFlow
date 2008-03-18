<? include 'compatibility_base.php'; ?>

<html>

<head>
  <title>Compatibility vs eta-ring</title>
  <meta content="Thomas Punz & Ronald Remington" name="author">
  <script type="text/javascript">
		<? generate_javascript("DeltaEtOverEtvsEta/DeltaEtOverEtvsEtaCompare_etBin"); ?>
  </script>
</head>

<body>

<style type="text/css">
	@import url("stylesheet.css");
</style>

<? 

	generate_map("DeltaEtOverEtvsEtadET_Score_vs_et", "DeltaEtOverEtvsEta/DeltaEtOverEtvsEtaCompare_etBin");
	generate_other_pictures("DeltaEtOverEtvsEtadEta_Allbins", "DeltaEtOverEtvsEtaSigmaDeltaEtOverEt_vs_Eta");
	
?>

</body>
</html>