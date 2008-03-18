<? include 'compatibility_base.php'; ?>

<html>

<head>
  <title>Compatibility vs eta-ring</title>
  <meta content="Thomas Punz & Ronald Remington" name="author">
  <script type="text/javascript">
		<? generate_javascript("DeltaEtOverEtvsPhi/DeltaEtOverEtvsPhiCompare_etBin"); ?>
  </script>
</head>

<body>

<style type="text/css">
	@import url("stylesheet.css");
</style>

<? 

	generate_map("DeltaEtOverEtvsPhidET_Score_vs_et", "DeltaEtOverEtvsPhi/DeltaEtOverEtvsPhiCompare_etBin");
	generate_other_pictures("DeltaEtOverEtvsPhidPhi_Allbins", "DeltaEtOverEtvsPhiSigmaDeltaEtOverEt_vs_Phi");
	
?>

</body>
</html>