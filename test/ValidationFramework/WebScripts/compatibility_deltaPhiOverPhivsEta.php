<? include 'compatibility_base.php'; ?>

<html>

<head>
  <title>Compatibility vs eta-ring</title>
  <meta content="Thomas Punz & Ronald Remington" name="author">
  <script type="text/javascript">
		<? generate_javascript("DeltaPhiOverPhivsEta/DeltaPhiOverPhivsEtaCompare_etBin"); ?>
  </script>
</head>

<body>

<style type="text/css">
	@import url("stylesheet.css");
</style>

<? 

	generate_map("DeltaPhiOverPhivsEtadET_Score_vs_et", "DeltaPhiOverPhivsEta/DeltaPhiOverPhivsEtaCompare_etBin");
	generate_other_pictures("DeltaPhiOverPhivsEtadEta_Allbins", "DeltaPhiOverPhivsEtaSigmaDeltaPhiOverPhi_vs_Eta");
	
?>

</body>
</html>