file = [placI185_v1.xml]

MoDeL
{
	part
	{
		biobrick id = [placI185_v1], name = [lacI repressed promoter (BBa_R0010)], originalConformation = [placI185]
		{
			interface
			{
				url:[http://2010.igem.org/Team:USTC_Software];
				shortDesc:[lacI repressed promoter, original conformation : placI185]; 
			}
			listOfConditionalParameters
			{
				conditionalParameter id = [forwardPromoterEfficiency], name = [efficiency as a promoter when transcripted forward], commonValue = [], units = [per_second]
				{
					parameterValue:[0.0] compartment = [E_coli];
				}
			}
			listOfReferencedSpecies
			{
				referencedSpecies:[placI185lacI153_4] partType = [ForwardDNA];
			}
		}
	}
}
