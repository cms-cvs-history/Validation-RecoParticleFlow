<? include 'compatibility_base.php'; ?>

<html>

<head>
  <title>Compatibility vs eta-ring</title>
  <meta content="Thomas Punz & Ronald Remington" name="author">
  <script type="text/javascript">
		<? generate_javascript("DeltaPhivsEta/DeltaPhivsEtaCompare_etBin"); ?>
  </script>
</head>

<body>

<style type="text/css">
	@import url("stylesheet.css");
</style>

<? 

	generate_map("DeltaPhivsEtadET_Score_vs_et", "DeltaPhivsEta/DeltaPhivsEtaCompare_etBin");
	generate_other_pictures("DeltaPhivsEtadEta_Allbins", "DeltaPhivsEtaSigmaDeltaPhi_vs_Eta");
	
?>

</body>
</html>