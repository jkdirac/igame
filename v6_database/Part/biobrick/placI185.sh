file = [placI185.xml]

MoDeL
{
	part
	{
		biobrick id = [placI185], name = [lacI-reg promoter (BBa_R0010)]
		{
			interface
			{
				url:[http://partsregistry.org/cgi/xml/part.cgi?part=BBa_R0010];
				shortDesc:[promoter (lacI repressor regulated)]; 
			}
			listOfConditionalParameters
			{
				conditionalParameter id = [forwardPromoterEfficiency], name = [efficiency as a promoter when transcripted forward], commonValue = [], units = [per_second]
				{
					parameterValue:[0.5] compartment = [E_coli];
				}
			}
			listOfReferencedSpecies
			{
				referencedSpecies:[placI185_dna] partType = [ForwardDNA];
				referencedSpecies:[placI185lacI153_4] partType = [ForwardDNA];
			}
		}
	}
}
